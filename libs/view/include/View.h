#pragma once

#include "Presenter.h"

#include <cmath>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <ranges>
#include <vector>

namespace TowerDefense {

    enum class State {
        START_SCREEN,
        IN_GAME,
        PAUSE_SCREEN
    };

    struct Menu {

        State current_state = State::START_SCREEN;
        sf::Texture start_screen_texture;
        sf::Sprite start_screen_sprite;

        sf::Text start_game_text;
        sf::RectangleShape start_game_button;
        bool is_start_button = false;

        sf::Text continue_text;
        sf::RectangleShape continue_button;
        bool is_continue_button = false;

        sf::Text exit_text;
        sf::RectangleShape exit_button;
        bool is_exit_button = false;


        sf::Text load_game_text;
        sf::RectangleShape load_game_button;
        bool is_load_button = false;

        sf::Text save_game_text;
        sf::RectangleShape save_game_button;
        bool is_save_button = false;

        sf::Text head_text;
    };

    struct HealthBar {
        sf::RectangleShape background;
        sf::RectangleShape fill;
        float max_health{};
    };

    struct Selection {
        sf::RectangleShape highlight;
        bool is_selected = false;
        size_t row = 0;
        size_t col = 0;
        ID tower_id = 0;
    };

    struct LineEffect {
        sf::Vector2f start_position;
        sf::Vector2f end_position;
        sf::Color color;
        float progress = 0.0f;
        float speed = 5.0f;
        bool active = true;
        sf::RectangleShape line;
        LineEffect(const sf::Vector2f &start, const sf::Vector2f &end, const sf::Color &col) : start_position(start), end_position(end), color(col) {
            line.setSize(sf::Vector2f(10.0f, 10.0f));
            line.setFillColor(col);
        }

        void update_line_effect(float dt) {
            if (!active) return;

            progress += speed * dt;
            if (progress >= 1.0f) {
                progress = 1.0f;
                active = false;
            }

            sf::Vector2f current_pos = start_position + (end_position - start_position) * progress;
            line.setPosition(current_pos);

            sf::Color current_color = color;
            current_color.a = static_cast<sf::Uint8>(255 * (1.0f - progress));
            line.setFillColor(current_color);
        }

        void draw(sf::RenderWindow &window) const {
            if (active) {
                window.draw(line);
            }
        }
    };

    struct DamageEffect {
        sf::Clock timer;
        float duration = 0.05f;
        bool active = false;
        sf::Color original_color;
    };

    struct CircleEffect {
        sf::Vector2f center;
        float range{};
        sf::Color color;
        float life_time = 0.0f;
        float max_lifetime = 0.5f;
        bool active = true;
        sf::CircleShape circle;

        CircleEffect(const sf::Vector2f& center_pos, float radius, const sf::Color& col)
            : center(center_pos), range(radius), color(col) {
            circle.setRadius(range);
            circle.setOrigin(range, range);
            circle.setPosition(center);
            circle.setFillColor(sf::Color(col.r, col.g, col.b, 100));
            circle.setOutlineThickness(2.0f);
            circle.setOutlineColor(col);
        }

        void update_circle_effect(float dt) {
            if (!active) return;

            life_time += dt;
            if (life_time >= max_lifetime) {
                active = false;
                return;
            }

            float pulse = 1.0f + 0.2f * std::sin(life_time * 10.0f);
            circle.setRadius(range * pulse);
            circle.setOrigin(range * pulse, range * pulse);

            float alpha = 100.0f * (1.0f - life_time / max_lifetime);
            circle.setFillColor(sf::Color(color.r, color.g, color.b, static_cast<sf::Uint8>(alpha)));

            alpha = 255.0f * (1.0f - life_time / max_lifetime);
            circle.setOutlineColor(sf::Color(color.r, color.g, color.b, static_cast<sf::Uint8>(alpha)));
        }

        void draw(sf::RenderWindow& window) const {
            if (active) {
                window.draw(circle);
            }
        }
    };

    class View {
        // consts
        static constexpr float TILE_SIZE = 64.0f;
        static constexpr float SPAWN_INTERVAL = 2.0f;
        static constexpr float ANIMATION_SPEED = 0.2f;

        // health_bar
        static constexpr float ENEMY_BAR_WIDTH = 40.0f;
        static constexpr float ENEMY_BAR_HEIGHT = 6.0f;
        static constexpr float ENEMY_BAR_OFFSET = -10.0f;

        static constexpr float CASTLE_BAR_WIDTH = 60.0f;
        static constexpr float CASTLE_BAR_HEIGHT = 10.0f;
        static constexpr float CASTLE_BAR_OFFSET = -15.0f;

        // colors
        inline static const sf::Color HEALTH_BAR_BG_COLOR = sf::Color(50, 50, 50, 200);
        inline static const sf::Color HEALTH_BAR_FILL_COLOR = sf::Color(0, 255, 0, 200);
        inline static const sf::Color LOW_HEALTH_COLOR = sf::Color(255, 0, 0, 200);

        // reference
        IPresenter &presenter_;
        sf::RenderWindow window_;
        sf::Font font_;

        // texture and sprite
        std::unordered_map<std::string, sf::Texture> landscape_textures_;
        sf::Texture castle_texture_;
        std::unordered_map<std::string, std::vector<sf::Texture>> tower_textures_;
        std::vector<sf::Texture> enemy_textures_;

        std::vector<std::vector<sf::Sprite>> landscape_sprites_;
        sf::Sprite castle_sprite_;
        std::unordered_map<ID, sf::Sprite> tower_sprites_;
        std::unordered_map<ID, std::pair<sf::Sprite, size_t>> enemy_sprites_;

        // bars
        HealthBar castle_health_bar_;
        std::unordered_map<ID, HealthBar> enemy_health_bars_;

        // selection
        Selection selection_;

        // effects
        std::vector<LineEffect> line_effects_;
        std::vector<CircleEffect> circle_effects_;
        std::unordered_map<ID, DamageEffect> damage_effects_;

        sf::Text gold_text_;

        // animation
        sf::Clock animation_clock_;
        size_t current_frame_ = 0;

        // menu
        Menu menu_;

        // views
        sf::View game_view_;
        sf::View ui_view_;



        void initialize_menu();
        void handle_menu_events(const sf::Event& event);
        void update_menu();
        void render_menu();
        void check_button(const sf::Vector2i& mouse_pos);

        void switch_to_game();
        void pause_game();
        void continue_game();
        void exit_game();

        // methods
        static sf::Vector2f get_tile_center(size_t row, size_t col);
        bool can_place_tower(size_t row, size_t col) const;
        bool can_place_trap(size_t row, size_t col) const;
        bool is_tower_at_tile(size_t row, size_t col) const;
        ID get_tower_id_at_tile(size_t row, size_t col) const;
        void load_textures();
        void initialize_map();
        void activate_damage_effect(ID enemy_id);
        void update_damage_effects();
        void create_effect(const sf::Vector2f &tower_pos, const sf::Vector2f &enemy_pos, const std::string &tower_type, float range);
        void update_effects(float dt);
        void create_enemy_health_bar(ID enemy_id, float health, float max_health);
        void update_enemy_health_bar(ID enemy_id, float health);
        void create_castle_health_bar(float health, float max_health);
        void update_castle_health_bar(float health);
        void update_castle();
        void update_towers();
        void update_enemies();
        void render_effects();
        void handle_events();
        void render();
        void load_game();
        void save_game();
        void check_game_over();
        sf::Vector2f get_screen_position(float screen_x, float screen_y) const;

    public:
        explicit View(IPresenter& presenter) : presenter_(presenter),
            window_(sf::VideoMode::getDesktopMode(), "Tower Defense", sf::Style::Fullscreen) {
            window_.setFramerateLimit(60);

            ui_view_ = window_.getDefaultView();

            initialize_menu();
            update_menu();
            load_textures();
        }

        void run();
    };
}