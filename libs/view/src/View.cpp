#include "View.h"
#include <unordered_set>


sf::Vector2f TowerDefense::View::get_tile_center(size_t row, size_t col) {
    return { static_cast<float>(col) * TILE_SIZE + TILE_SIZE / 2.0f,
                static_cast<float>(row) * TILE_SIZE + TILE_SIZE / 2.0f };
}

bool TowerDefense::View::can_place_tower(size_t row, size_t col) const {
    auto map_dto = presenter_.get_map();
    return map_dto.landscape_type[row][col] == "grass";
}

bool TowerDefense::View::can_place_trap(size_t row, size_t col) const {
    auto map_dto = presenter_.get_map();
    return map_dto.landscape_type[row][col] == "road";
}

bool TowerDefense::View::is_tower_at_tile(size_t row, size_t col) const {
    auto towers_dto = presenter_.get_towers();
    for (const auto &tower : towers_dto) {
        if (tower.x == row && tower.y == col) {
            return true;
        }
    }
    return false;
}

TowerDefense::ID TowerDefense::View::get_tower_id_at_tile(size_t row, size_t col) const {
    auto towers_dto = presenter_.get_towers();
    for (const auto &tower : towers_dto) {
        if (tower.x == row && tower.y == col) {
            return tower.id;
        }
    }
    return 0;
}

void TowerDefense::View::load_textures() {
    sf::Texture texture;

    texture.loadFromFile("../images/road.jpg");
    landscape_textures_["road"] = texture;
    texture.loadFromFile("../images/grass.jpg");
    landscape_textures_["grass"] = texture;
    texture.loadFromFile("../images/field.jpg");
    landscape_textures_["field"] = texture;
    texture.loadFromFile("../images/forest.jpg");
    landscape_textures_["forest"] = texture;

    texture.loadFromFile("../images/enemy1.png");
    enemy_textures_.push_back(texture);
    texture.loadFromFile("../images/enemy2.png");
    enemy_textures_.push_back(texture);
    texture.loadFromFile("../images/enemy3.png");
    enemy_textures_.push_back(texture);
    texture.loadFromFile("../images/enemy4.png");
    enemy_textures_.push_back(texture);

    texture.loadFromFile("../images/simple_tower_1.png");
    tower_textures_["simple_tower"].push_back(texture);
    texture.loadFromFile("../images/simple_tower_2.png");
    tower_textures_["simple_tower"].push_back(texture);
    texture.loadFromFile("../images/simple_tower_3.png");
    tower_textures_["simple_tower"].push_back(texture);

    texture.loadFromFile("../images/magic_trap.png");
    tower_textures_["magic_trap"].push_back(texture);
    texture.loadFromFile("../images/magic_trap.png");
    tower_textures_["magic_trap"].push_back(texture);
    texture.loadFromFile("../images/magic_trap.png");
    tower_textures_["magic_trap"].push_back(texture);

    texture.loadFromFile("../images/magic_tower_1.png");
    tower_textures_["magic_tower"].push_back(texture);
    texture.loadFromFile("../images/magic_tower_2.png");
    tower_textures_["magic_tower"].push_back(texture);
    texture.loadFromFile("../images/magic_tower_3.png");
    tower_textures_["magic_tower"].push_back(texture);

    castle_texture_.loadFromFile("../images/castle.png");
    castle_sprite_.setTexture(castle_texture_);

    font_.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono-Oblique.ttf");
    gold_text_.setFont(font_);
    gold_text_.setCharacterSize(40);
    gold_text_.setFillColor(sf::Color::Yellow);
    gold_text_.setStyle(sf::Text::Bold);
}

void TowerDefense::View::initialize_map() {
    auto map_dto = presenter_.get_map();
    landscape_sprites_.clear();

    for (size_t i = 0; i < map_dto.height; i++) {
        std::vector<sf::Sprite> row;
        for (size_t j = 0; j < map_dto.width; j++) {
            std::string type = map_dto.landscape_type[i][j];
            sf::Sprite sprite(landscape_textures_.at(type));
            sprite.setPosition(static_cast<float>(j) * TILE_SIZE, static_cast<float>(i) * TILE_SIZE);
            row.push_back(sprite);
        }
        landscape_sprites_.push_back(row);
    }

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    window_.setSize(sf::Vector2u(desktopMode.width, desktopMode.height));

    float map_width = static_cast<float>(map_dto.width) * TILE_SIZE;
    float map_height = static_cast<float>(map_dto.height) * TILE_SIZE;

    float scale_x = static_cast<float>(desktopMode.width) / map_width;
    float scale_y = static_cast<float>(desktopMode.height) / map_height;


    game_view_.setCenter(map_width / 2.0f, map_height / 2.0f);

    if (scale_x < scale_y) {
        game_view_.setSize(map_width, map_height * (scale_y / scale_x));
    } else {
        game_view_.setSize(map_width * (scale_x / scale_y), map_height);
    }

    selection_.highlight.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    selection_.highlight.setFillColor(sf::Color(255, 255, 255, 100));
    selection_.highlight.setOutlineThickness(2.0f);
    selection_.highlight.setOutlineColor(sf::Color::White);
}

void TowerDefense::View::activate_damage_effect(ID enemy_id) {
    auto enemy_it = enemy_sprites_.find(enemy_id);
    if (enemy_it != enemy_sprites_.end()) {
        DamageEffect effect;
        effect.timer.restart();
        effect.active = true;
        effect.original_color = enemy_it->second.first.getColor();
        damage_effects_[enemy_id] = effect;
    }
}

void TowerDefense::View::update_damage_effects() {
    std::vector<ID> effects_to_remove;

    for (auto &[id, effect] : damage_effects_) {
        if (effect.active) {
            auto enemy_it = enemy_sprites_.find(id);
            if (enemy_it != enemy_sprites_.end()) {
                float time = effect.timer.getElapsedTime().asSeconds();
                if (time < effect.duration) {
                    sf::Color damage_color(255, 100, 100, 200);
                    enemy_it->second.first.setColor(damage_color);
                } else {
                    enemy_it->second.first.setColor(effect.original_color);
                    effect.active = false;
                    effects_to_remove.push_back(id);
                }
            }
        }
    }

    for (ID id : effects_to_remove) {
        damage_effects_.erase(id);
    }
}

void TowerDefense::View::create_effect(const sf::Vector2f &tower_pos, const sf::Vector2f &enemy_pos, const std::string &tower_type, float range) {
    sf::Color effect_color;

    if (tower_type.find("simple_tower") != std::string::npos) {
        effect_color = sf::Color::Yellow;
        LineEffect effect{tower_pos, enemy_pos, effect_color};
        line_effects_.push_back(effect);
    } else if (tower_type.find("magic_tower") != std::string::npos) {
        effect_color = sf::Color::Magenta;
        LineEffect effect{tower_pos, enemy_pos, effect_color};
        line_effects_.push_back(effect);
    } else if (tower_type.find("magic_trap") != std::string::npos) {
        CircleEffect circle_effect{tower_pos, range * 60, sf::Color::Cyan};
        circle_effects_.push_back(circle_effect);
    } else {
        throw std::runtime_error("Unknown effect");
    }
}

void TowerDefense::View::update_effects(float dt) {
    for (auto it = line_effects_.begin(); it != line_effects_.end(); ) {
        it->update_line_effect(dt);
        if (!it->active) {
            it = line_effects_.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = circle_effects_.begin(); it != circle_effects_.end(); ) {
        it->update_circle_effect(dt);
        if (!it->active) {
            it = circle_effects_.erase(it);
        } else {
            ++it;
        }
    }
}

void TowerDefense::View::create_enemy_health_bar(ID enemy_id, float health, float max_health) {
    auto enemy_sprite_it = enemy_sprites_.find(enemy_id);
    if (enemy_sprite_it != enemy_sprites_.end()) {
        HealthBar health_bar;
        const auto &enemy_sprite = enemy_sprite_it->second.first;
        sf::FloatRect bounds = enemy_sprite.getGlobalBounds();

        float enemy_center_x = bounds.left + bounds.width / 2.0f;

        float bar_x = enemy_center_x - ENEMY_BAR_WIDTH / 2.0f;
        float bar_y = bounds.top + ENEMY_BAR_OFFSET;

        health_bar.background.setSize(sf::Vector2f(ENEMY_BAR_WIDTH, ENEMY_BAR_HEIGHT));
        health_bar.background.setFillColor(HEALTH_BAR_BG_COLOR);
        health_bar.background.setPosition(bar_x, bar_y);

        float health_С = health / max_health;
        float fill_width = ENEMY_BAR_WIDTH * health_С;
        health_bar.fill.setSize(sf::Vector2f(fill_width, ENEMY_BAR_HEIGHT));

        if (health_С > 0.5f) {
            health_bar.fill.setFillColor(HEALTH_BAR_FILL_COLOR);
        } else if (health_С > 0.25f) {
            health_bar.fill.setFillColor(sf::Color(255, 170, 0, 200));
        } else {
            health_bar.fill.setFillColor(LOW_HEALTH_COLOR);
        }

        health_bar.fill.setPosition(bar_x, bar_y);
        health_bar.max_health = max_health;

        enemy_health_bars_[enemy_id] = health_bar;
    }
}

void TowerDefense::View::update_enemy_health_bar(ID enemy_id, float health) {
    auto enemy_health_bar_it = enemy_health_bars_.find(enemy_id);
    auto enemy_sprite_it = enemy_sprites_.find(enemy_id);

    if (enemy_health_bar_it != enemy_health_bars_.end() && enemy_sprite_it != enemy_sprites_.end()) {
        const auto &enemy_sprite = enemy_sprite_it->second.first;
        sf::FloatRect bounds = enemy_sprite.getGlobalBounds();

        float enemy_center_x = bounds.left + bounds.width / 2.0f;

        float bar_x = enemy_center_x - ENEMY_BAR_WIDTH / 2.0f;
        float bar_y = bounds.top + ENEMY_BAR_OFFSET;

        enemy_health_bar_it->second.background.setPosition(bar_x, bar_y);

        float health_percentage = health / enemy_health_bar_it->second.max_health;
        float fill_width = ENEMY_BAR_WIDTH * health_percentage;
        enemy_health_bar_it->second.fill.setSize(sf::Vector2f(fill_width, ENEMY_BAR_HEIGHT));
        enemy_health_bar_it->second.fill.setPosition(bar_x, bar_y);

        if (health_percentage > 0.5f) {
            enemy_health_bar_it->second.fill.setFillColor(HEALTH_BAR_FILL_COLOR);
        } else if (health_percentage > 0.25f) {
            enemy_health_bar_it->second.fill.setFillColor(sf::Color(255, 165, 0, 200));
        } else {
            enemy_health_bar_it->second.fill.setFillColor(LOW_HEALTH_COLOR);
        }
    }
}

void TowerDefense::View::create_castle_health_bar(float health, float max_health) {
    castle_health_bar_.background.setSize(sf::Vector2f(CASTLE_BAR_WIDTH, CASTLE_BAR_HEIGHT));
    castle_health_bar_.background.setFillColor(HEALTH_BAR_BG_COLOR);
    castle_health_bar_.fill.setSize(sf::Vector2f(CASTLE_BAR_WIDTH, CASTLE_BAR_HEIGHT));
    castle_health_bar_.max_health = max_health;
    update_castle_health_bar(health);
}

void TowerDefense::View::update_castle_health_bar(float health) {
    sf::FloatRect castle_bounds = castle_sprite_.getGlobalBounds();

    constexpr float castle_health_bar_width = 60.0f;
    constexpr float castle_health_bar_height = 10.0f;
    constexpr float castle_health_bar_offset_y = -15.0f;

    float castle_center_x = castle_bounds.left + castle_bounds.width / 2.0f;
    float bar_x = castle_center_x - castle_health_bar_width / 2.0f;
    float bar_y = castle_bounds.top + castle_health_bar_offset_y;

    castle_health_bar_.background.setPosition(bar_x, bar_y);

    float health_percentage = health / castle_health_bar_.max_health;
    float fill_width = castle_health_bar_width * health_percentage;
    castle_health_bar_.fill.setSize(sf::Vector2f(fill_width, castle_health_bar_height));
    castle_health_bar_.fill.setPosition(bar_x, bar_y);

    if (health_percentage > 0.5f) {
        castle_health_bar_.fill.setFillColor(HEALTH_BAR_FILL_COLOR);
    } else if (health_percentage > 0.25f) {
        castle_health_bar_.fill.setFillColor(sf::Color(255, 165, 0, 200));
    } else {
        castle_health_bar_.fill.setFillColor(LOW_HEALTH_COLOR);
    }
}

void TowerDefense::View::update_castle() {
    CastleDTO castle_dto = presenter_.get_castle();

    auto castle_center = get_tile_center(castle_dto.y, castle_dto.x);
    sf::FloatRect castle_bounds = castle_sprite_.getLocalBounds();
    castle_sprite_.setOrigin(castle_bounds.width / 2.0f, castle_bounds.height / 2.0f);
    castle_sprite_.setPosition(castle_center);

    float scale = TILE_SIZE / std::max(castle_bounds.width, castle_bounds.height) * 1.2f;
    castle_sprite_.setScale(scale, scale);

    gold_text_.setString("Gold: " + std::to_string(castle_dto.gold));

    sf::Vector2u window_size = window_.getSize();
    sf::FloatRect text_bounds = gold_text_.getLocalBounds();


    float screen_x = static_cast<float>(window_size.x) - text_bounds.width - 30.0f;
    float screen_y = 10.0f;


    sf::Vector2f ui_pos = window_.mapPixelToCoords(sf::Vector2i(static_cast<int>(screen_x), static_cast<int>(screen_y)), ui_view_);
    gold_text_.setPosition(ui_pos);

    if (castle_health_bar_.max_health == 0.0f) {
        create_castle_health_bar(castle_dto.health, castle_dto.max_health);
    } else {
        update_castle_health_bar(castle_dto.health);
    }
}

void TowerDefense::View::update_towers() {
    auto towers_dto = presenter_.get_towers();
    for (const auto &tower_dto : towers_dto) {
        sf::Sprite tower_sprite;
        tower_sprite.setTexture(tower_textures_.at(tower_dto.type).at(tower_dto.level - 1));

        auto center = get_tile_center(tower_dto.x, tower_dto.y);
        tower_sprite.setPosition(center);

        sf::FloatRect bounds = tower_sprite.getLocalBounds();
        tower_sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

        float scale = TILE_SIZE / std::max(bounds.width, bounds.height);
        tower_sprite.setScale(scale, scale);

        tower_sprites_[tower_dto.id] = tower_sprite;
    }
}

void TowerDefense::View::update_enemies() {
    auto enemies_dto = presenter_.get_enemies();

    if (animation_clock_.getElapsedTime().asSeconds() >= ANIMATION_SPEED) {
        animation_clock_.restart();
        current_frame_ = (current_frame_ + 1) % enemy_textures_.size();
    }

    std::unordered_set<ID> alive_enemies;
    for (const auto &enemy : enemies_dto) {
        alive_enemies.insert(enemy.id);

        auto it = enemy_sprites_.find(enemy.id);
        if (it == enemy_sprites_.end()) {
            sf::Sprite enemy_sprite(enemy_textures_[0]);
            enemy_sprite.setPosition(enemy.x_pixels, enemy.y_pixels);
            float scale = TILE_SIZE / static_cast<float>(std::max(enemy_textures_[0].getSize().x, enemy_textures_[0].getSize().y));
            enemy_sprite.setScale(scale, scale);
            enemy_sprites_[enemy.id] = {enemy_sprite, 0};
            create_enemy_health_bar(enemy.id, enemy.health, enemy.max_health);
        } else {
            it->second.first.setPosition(enemy.x_pixels, enemy.y_pixels);
            it->second.second = current_frame_;
            it->second.first.setTexture(enemy_textures_[current_frame_]);
            update_enemy_health_bar(enemy.id, enemy.health);
        }
    }

    std::vector<ID> enemies_to_remove;
    for (const auto& id : enemy_sprites_ | std::views::keys) {
        if (!alive_enemies.contains(id)) {
            enemies_to_remove.push_back(id);
        }
    }

    for (ID dead_id : enemies_to_remove) {
        enemy_sprites_.erase(dead_id);
        enemy_health_bars_.erase(dead_id);
        damage_effects_.erase(dead_id);
    }
}

void TowerDefense::View::render_effects() {
    for (const auto &effect : line_effects_) {
        effect.draw(window_);
    }

    for (const auto &effect : circle_effects_) {
        effect.draw(window_);
    }
}

void TowerDefense::View::handle_events() {
    sf::Event event{};
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        }

        if (menu_.current_state != State::IN_GAME) {
            handle_menu_events(event);
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                pause_game();
                continue;
            }

            if (selection_.is_selected) {
                if (event.key.code == sf::Keyboard::S) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
                        if (can_place_tower(selection_.row, selection_.col)) {
                            presenter_.add_tower("simple_tower_nearest_to_tower_strategy", selection_.row, selection_.col);
                            update_towers();
                            selection_.is_selected = false;
                            selection_.tower_id = 0;
                        }
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
                        if (can_place_tower(selection_.row, selection_.col)) {
                            presenter_.add_tower("simple_tower_nearest_to_castle_strategy", selection_.row, selection_.col);
                            update_towers();
                            selection_.is_selected = false;
                            selection_.tower_id = 0;
                        }
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
                        if (can_place_tower(selection_.row, selection_.col)) {
                            presenter_.add_tower("simple_tower_strongest_strategy", selection_.row, selection_.col);
                            update_towers();
                            selection_.is_selected = false;
                            selection_.tower_id = 0;
                        }
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
                        if (can_place_tower(selection_.row, selection_.col)) {
                            presenter_.add_tower("simple_tower_weakest_strategy", selection_.row, selection_.col);
                            update_towers();
                            selection_.is_selected = false;
                            selection_.tower_id = 0;
                        }
                    }
                } else if (event.key.code == sf::Keyboard::M) {
                    if (can_place_tower(selection_.row, selection_.col)) {
                        presenter_.add_tower("magic_tower_weakest_strategy_poison_effect", selection_.row, selection_.col);
                        update_towers();
                        selection_.is_selected = false;
                        selection_.tower_id = 0;
                    }
                } else if (event.key.code == sf::Keyboard::T) {
                    if (can_place_trap(selection_.row, selection_.col)) {
                        presenter_.add_tower("magic_trap_all_in_range_strategy_slow_effect", selection_.row, selection_.col);
                        update_towers();
                        selection_.is_selected = false;
                        selection_.tower_id = 0;
                    }
                } else if (event.key.code == sf::Keyboard::U && selection_.tower_id > 0) {
                    presenter_.upgrade_tower(selection_.tower_id);
                    update_towers();
                    selection_.is_selected = false;
                    selection_.tower_id = 0;
                }
            }
        } else if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);
            sf::Vector2f world_pos = window_.mapPixelToCoords(mouse_pos, game_view_);

            auto tile_row = static_cast<size_t>(world_pos.y / TILE_SIZE);
            auto tile_col = static_cast<size_t>(world_pos.x / TILE_SIZE);

            if (event.mouseButton.button == sf::Mouse::Left) {
                selection_.row = tile_row;
                selection_.col = tile_col;
                selection_.is_selected = true;
                selection_.tower_id = get_tower_id_at_tile(tile_row, tile_col);
                selection_.highlight.setPosition(static_cast<float>(tile_col) * TILE_SIZE, static_cast<float>(tile_row) * TILE_SIZE);
            } else if (event.mouseButton.button == sf::Mouse::Right) {
                selection_.is_selected = false;
                selection_.tower_id = 0;
            }
        }
    }
}

void TowerDefense::View::render() {
    window_.clear(sf::Color::Black);

    if (menu_.current_state != State::IN_GAME) {
        render_menu();
        window_.display();
        return;
    }

    window_.setView(game_view_);

    for (const auto &row : landscape_sprites_) {
        for (const auto &sprite : row) {
            window_.draw(sprite);
        }
    }

    if (selection_.is_selected) {
        window_.draw(selection_.highlight);
    }

    window_.draw(castle_sprite_);

    if (castle_health_bar_.max_health > 0.0f) {
        window_.draw(castle_health_bar_.background);
        window_.draw(castle_health_bar_.fill);
    }

    for (const auto &val : tower_sprites_ | std::views::values) {
        window_.draw(val);
    }

    for (const auto &sprite_pair : enemy_sprites_ | std::views::values) {
        window_.draw(sprite_pair.first);
    }

    render_effects();
    for (const auto& val : enemy_health_bars_ | std::views::values) {
        window_.draw(val.background);
        window_.draw(val.fill);
    }

    window_.setView(ui_view_);
    window_.draw(gold_text_);

    window_.setView(game_view_);

    window_.display();
}
void TowerDefense::View::run() {
    sf::Clock clock;
    sf::Clock spawn_clock;

    while (window_.isOpen()) {
        float dt = clock.restart().asSeconds();
        handle_events();

        if (menu_.current_state != State::IN_GAME) {
            window_.clear();
            render_menu();
            window_.display();
            continue;
        }

        check_game_over();

        if (menu_.current_state != State::IN_GAME) {
            continue;
        }

        float current_spawn_interval = SPAWN_INTERVAL;
        float decrease_rate = 0.0001f;
        float min_spawn_interval = 0.5f;

        if (spawn_clock.getElapsedTime().asSeconds() >= current_spawn_interval) {
            spawn_clock.restart();
            presenter_.add_enemy();
        }

        current_spawn_interval = std::max(current_spawn_interval - decrease_rate, min_spawn_interval);

        presenter_.move(dt);

        auto attacks_info = presenter_.tower_attack(dt);
        for (const auto &attack_info: attacks_info) {
            auto tower_pos = get_tile_center(attack_info.tower_x, attack_info.tower_y);
            sf::Vector2f enemy_pos(attack_info.enemy_x_pixels, attack_info.enemy_y_pixels);
            create_effect(tower_pos, enemy_pos, attack_info.tower_type, attack_info.range);
            activate_damage_effect(attack_info.enemy_id);
        }

        presenter_.enemy_attack();

        update_castle();
        update_enemies();
        update_towers();
        update_effects(dt);
        update_damage_effects();
        render();
    }
}
void TowerDefense::View::update_menu() {
    sf::Vector2u window_size = window_.getSize();

    menu_.start_screen_sprite.setScale(
        static_cast<float>(window_size.x) / static_cast<float>(menu_.start_screen_texture.getSize().x),
        static_cast<float>(window_size.y) / static_cast<float>(menu_.start_screen_texture.getSize().y) );

    sf::FloatRect title_bounds = menu_.head_text.getLocalBounds();
    menu_.head_text.setOrigin(title_bounds.width / 2, title_bounds.height / 2);
    menu_.head_text.setPosition(static_cast<float>(window_size.x) / 2.0f, static_cast<float>(window_size.y) / 4.0f);

    float start_x = static_cast<float>(window_size.x) / 2.0f - 250;

    if (menu_.current_state == State::START_SCREEN) {
        float button_spacing = 90.0f;
        float start_y = static_cast<float>(window_size.y) / 2.0f - button_spacing / 2;

        menu_.start_game_button.setPosition(start_x, start_y);
        menu_.load_game_button.setPosition(start_x, start_y + button_spacing);

        sf::FloatRect start_text_bounds = menu_.start_game_text.getLocalBounds();
        menu_.start_game_text.setOrigin(start_text_bounds.width / 2, 0);
        float start_text_y = start_y + (70.0f - start_text_bounds.height) / 2.0f - 5.0f;
        menu_.start_game_text.setPosition(start_x + 250, start_text_y);

        sf::FloatRect load_text_bounds = menu_.load_game_text.getLocalBounds();
        menu_.load_game_text.setOrigin(load_text_bounds.width / 2, 0);
        float load_text_y = start_y + button_spacing + (70.0f - load_text_bounds.height) / 2.0f - 5.0f;
        menu_.load_game_text.setPosition(start_x + 250, load_text_y);
    } else if (menu_.current_state == State::PAUSE_SCREEN) {
        float button_spacing = 90.0f;
        float base_y = static_cast<float>(window_size.y) / 2.0f - button_spacing;
        float continue_y = base_y;
        float save_y = continue_y + button_spacing;
        float exit_y = save_y + button_spacing;

        menu_.continue_button.setPosition(start_x, continue_y);
        menu_.save_game_button.setPosition(start_x, save_y);
        menu_.exit_button.setPosition(start_x, exit_y);

        sf::FloatRect continue_bounds = menu_.continue_text.getLocalBounds();
        menu_.continue_text.setOrigin(continue_bounds.width / 2, 0);
        float continue_text_y = continue_y + (70.0f - continue_bounds.height) / 2.0f - 5.0f;
        menu_.continue_text.setPosition(start_x + 250, continue_text_y);

        sf::FloatRect save_bounds = menu_.save_game_text.getLocalBounds();
        menu_.save_game_text.setOrigin(save_bounds.width / 2, 0);
        float save_text_y = save_y + (70.0f - save_bounds.height) / 2.0f - 5.0f;
        menu_.save_game_text.setPosition(start_x + 250, save_text_y);

        sf::FloatRect exit_bounds = menu_.exit_text.getLocalBounds();
        menu_.exit_text.setOrigin(exit_bounds.width / 2, 0);
        float exit_text_y = exit_y + (70.0f - exit_bounds.height) / 2.0f - 5.0f;
        menu_.exit_text.setPosition(start_x + 250, exit_text_y);
    }
}

void TowerDefense::View::initialize_menu() {

    menu_.start_screen_texture.loadFromFile("../images/background.jpg");
    menu_.start_screen_sprite.setTexture(menu_.start_screen_texture);

    font_.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono-Oblique.ttf");

    menu_.head_text.setFont(font_);
    menu_.head_text.setString("TOWER DEFENSE");
    menu_.head_text.setCharacterSize(80);
    menu_.head_text.setFillColor(sf::Color::Yellow);
    menu_.head_text.setStyle(sf::Text::Bold | sf::Text::Italic);

    menu_.start_game_button.setSize(sf::Vector2f(500, 70));
    menu_.start_game_button.setFillColor(sf::Color(0, 100, 0, 200));
    menu_.start_game_button.setOutlineThickness(3);
    menu_.start_game_button.setOutlineColor(sf::Color::Green);

    menu_.load_game_button.setSize(sf::Vector2f(500, 70));
    menu_.load_game_button.setFillColor(sf::Color(70, 70, 200, 200));
    menu_.load_game_button.setOutlineThickness(3);
    menu_.load_game_button.setOutlineColor(sf::Color::Blue);

    menu_.continue_button.setSize(sf::Vector2f(500, 70));
    menu_.continue_button.setFillColor(sf::Color(0, 100, 0, 200));
    menu_.continue_button.setOutlineThickness(3);
    menu_.continue_button.setOutlineColor(sf::Color::Green);

    menu_.save_game_button.setSize(sf::Vector2f(500, 70));
    menu_.save_game_button.setFillColor(sf::Color(200, 200, 0, 200));
    menu_.save_game_button.setOutlineThickness(3);
    menu_.save_game_button.setOutlineColor(sf::Color::Yellow);

    menu_.exit_button.setSize(sf::Vector2f(500, 70));
    menu_.exit_button.setFillColor(sf::Color(100, 0, 0, 200));
    menu_.exit_button.setOutlineThickness(3);
    menu_.exit_button.setOutlineColor(sf::Color::Red);

    menu_.start_game_text.setFont(font_);
    menu_.start_game_text.setString("START NEW GAME");
    menu_.start_game_text.setCharacterSize(45);
    menu_.start_game_text.setFillColor(sf::Color::White);

    menu_.load_game_text.setFont(font_);
    menu_.load_game_text.setString("LOAD SAVED GAME");
    menu_.load_game_text.setCharacterSize(45);
    menu_.load_game_text.setFillColor(sf::Color::White);

    menu_.continue_text.setFont(font_);
    menu_.continue_text.setString("CONTINUE");
    menu_.continue_text.setCharacterSize(45);
    menu_.continue_text.setFillColor(sf::Color::White);

    menu_.save_game_text.setFont(font_);
    menu_.save_game_text.setString("SAVE GAME");
    menu_.save_game_text.setCharacterSize(45);
    menu_.save_game_text.setFillColor(sf::Color::White);

    menu_.exit_text.setFont(font_);
    menu_.exit_text.setString("EXIT");
    menu_.exit_text.setCharacterSize(45);
    menu_.exit_text.setFillColor(sf::Color::White);

    update_menu();
}
void TowerDefense::View::check_button(const sf::Vector2i& mouse_pos) {
    sf::Vector2f world_pos = window_.mapPixelToCoords(mouse_pos, ui_view_);

    if (menu_.current_state == State::START_SCREEN) {
        sf::Vector2f start_button_pos = menu_.start_game_button.getPosition();
        sf::FloatRect start_button_bounds(start_button_pos.x, start_button_pos.y, menu_.start_game_button.getSize().x, menu_.start_game_button.getSize().y);

        sf::Vector2f load_button_pos = menu_.load_game_button.getPosition();
        sf::FloatRect load_button_bounds(load_button_pos.x, load_button_pos.y, menu_.load_game_button.getSize().x, menu_.load_game_button.getSize().y);

        menu_.is_start_button = start_button_bounds.contains(world_pos);
        if (menu_.is_start_button) {
            menu_.start_game_button.setFillColor(sf::Color(0, 150, 0, 200));
        } else {
            menu_.start_game_button.setFillColor(sf::Color(0, 100, 0, 200));
        }

        menu_.is_load_button = load_button_bounds.contains(world_pos);
        if (menu_.is_load_button) {
            menu_.load_game_button.setFillColor(sf::Color(100, 100, 255, 200));
        } else {
            menu_.load_game_button.setFillColor(sf::Color(70, 70, 200, 200));
        }
    } else if (menu_.current_state == State::PAUSE_SCREEN) {
        sf::Vector2f continue_button_pos = menu_.continue_button.getPosition();
        sf::FloatRect continue_button_bounds(continue_button_pos.x, continue_button_pos.y, menu_.continue_button.getSize().x, menu_.continue_button.getSize().y);

        sf::Vector2f save_button_pos = menu_.save_game_button.getPosition();
        sf::FloatRect save_button_bounds(save_button_pos.x, save_button_pos.y, menu_.save_game_button.getSize().x, menu_.save_game_button.getSize().y);

        sf::Vector2f exit_button_pos = menu_.exit_button.getPosition();
        sf::FloatRect exit_button_bounds(exit_button_pos.x, exit_button_pos.y, menu_.exit_button.getSize().x, menu_.exit_button.getSize().y);

        menu_.is_continue_button = continue_button_bounds.contains(world_pos);
        if (menu_.is_continue_button) {
            menu_.continue_button.setFillColor(sf::Color(0, 150, 0, 200));
        } else {
            menu_.continue_button.setFillColor(sf::Color(0, 100, 0, 200));
        }

        menu_.is_save_button = save_button_bounds.contains(world_pos);
        if (menu_.is_save_button) {
            menu_.save_game_button.setFillColor(sf::Color(255, 255, 100, 200));
        } else {
            menu_.save_game_button.setFillColor(sf::Color(200, 200, 0, 200));
        }

        menu_.is_exit_button = exit_button_bounds.contains(world_pos);
        if (menu_.is_exit_button) {
            menu_.exit_button.setFillColor(sf::Color(150, 0, 0, 200));
        } else {
            menu_.exit_button.setFillColor(sf::Color(100, 0, 0, 200));
        }
    }
}
void TowerDefense::View::handle_menu_events(const sf::Event &event) {
    if (event.type == sf::Event::MouseMoved) {
        check_button(sf::Mouse::getPosition(window_));
    } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);
            check_button(mouse_pos);

            if (menu_.current_state == State::START_SCREEN) {
                if (menu_.is_start_button) {
                    switch_to_game();
                } else if (menu_.is_load_button) {
                    load_game();
                }
            } else if (menu_.current_state == State::PAUSE_SCREEN) {
                if (menu_.is_continue_button) {
                    continue_game();
                } else if (menu_.is_save_button) {
                    save_game();
                } else if (menu_.is_exit_button) {
                    exit_game();
                }
            }
        }
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            if (menu_.current_state == State::IN_GAME) {
                pause_game();
            } else if (menu_.current_state == State::PAUSE_SCREEN) {
                continue_game();
            }
        } else if (event.key.code == sf::Keyboard::Enter) {
            if (menu_.current_state == State::START_SCREEN) {
                switch_to_game();
            }
        }
    }
}

void TowerDefense::View::switch_to_game() {
    menu_.current_state = State::IN_GAME;
    initialize_map();
    update_castle();
    update_towers();
    window_.setView(game_view_);
    update_menu();
}

void TowerDefense::View::load_game() {
    presenter_.load();
    menu_.current_state = State::IN_GAME;
    initialize_map();
    update_castle();
    update_towers();
    update_enemies();
    window_.setView(game_view_);
    update_menu();

}

void TowerDefense::View::save_game() {
    presenter_.save();
    menu_.save_game_text.setString("SAVED");
    sf::sleep(sf::seconds(1.0f));
    menu_.save_game_text.setString("SAVE GAME");
}

void TowerDefense::View::pause_game() {
    menu_.current_state = State::PAUSE_SCREEN;
    window_.setView(ui_view_);
    update_menu();
}
void TowerDefense::View::continue_game() {
    menu_.current_state = State::IN_GAME;
    window_.setView(game_view_);
    update_menu();
}

void TowerDefense::View::exit_game() {
    window_.close();
}

void TowerDefense::View::render_menu() {
    window_.setView(ui_view_);

    window_.draw(menu_.start_screen_sprite);

    sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(window_.getSize().x), static_cast<float>(window_.getSize().y)));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window_.draw(overlay);

    window_.draw(menu_.head_text);

    if (menu_.current_state == State::START_SCREEN) {
        window_.draw(menu_.start_game_button);
        window_.draw(menu_.start_game_text);
        window_.draw(menu_.load_game_button);
        window_.draw(menu_.load_game_text);
    }
    else if (menu_.current_state == State::PAUSE_SCREEN) {
        window_.draw(menu_.continue_button);
        window_.draw(menu_.continue_text);
        window_.draw(menu_.save_game_button);
        window_.draw(menu_.save_game_text);
        window_.draw(menu_.exit_button);
        window_.draw(menu_.exit_text);
    }

    sf::Text instruction;
    instruction.setFont(font_);
    instruction.setCharacterSize(24);
    instruction.setFillColor(sf::Color::White);

    if (menu_.current_state == State::START_SCREEN) {
        instruction.setString("Press ENTER or click START to begin");
    }
    else if (menu_.current_state == State::PAUSE_SCREEN) {
        instruction.setString("Press ESC or click CONTINUE to resume");
    }

    sf::FloatRect instr_bounds = instruction.getLocalBounds();
    instruction.setOrigin(instr_bounds.width / 2, instr_bounds.height / 2);
    instruction.setPosition(static_cast<float>(window_.getSize().x) / 2.0f, static_cast<float>(window_.getSize().y - 50));
    window_.draw(instruction);
}

sf::Vector2f TowerDefense::View::get_screen_position(float screen_x, float screen_y) const {
    sf::Vector2f pixel_pos(screen_x, screen_y);
    return window_.mapPixelToCoords(static_cast<sf::Vector2i>(pixel_pos), ui_view_);
}

void TowerDefense::View::check_game_over() {
    CastleDTO castle_dto = presenter_.get_castle();
    if (castle_dto.health <= 0.0f) {
        menu_.current_state = State::START_SCREEN;



        presenter_.reset();

        enemy_sprites_.clear();
        enemy_health_bars_.clear();
        tower_sprites_.clear();
        line_effects_.clear();
        circle_effects_.clear();
        damage_effects_.clear();

        selection_.is_selected = false;
        selection_.tower_id = 0;

        castle_health_bar_.max_health = 0.0f;

        window_.setView(ui_view_);
        update_menu();
    }
}