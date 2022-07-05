#include <simulator/sim.h>

#include <iostream>
#include <string>
#include "imgui.h"
#include "imgui-SFML.h"


#include <chrono>
#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

void draw_field() {
    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)); //make a rectangle to add background color
    background.setFillColor(sf::Color(141, 158, 196));
    background.setPosition(0, 0);
    window_->draw(background);
    sf::CircleShape dohyo; //create the circle that represents the dohyo. Input is radius
    dohyo.setRadius(vis_scale*75.f);
    dohyo.setFillColor(sf::Color(0, 0, 0)); //color the dohyo black
    dohyo.setOutlineThickness(vis_scale*2.f); //give dohyo an outline
    dohyo.setOutlineColor(sf::Color(250, 250, 250)); //make the outline white
    dohyo.setPosition((WINDOW_WIDTH/2)-vis_scale*75, (WINDOW_HEIGHT/2)-vis_scale*75);
    window_->draw(dohyo);
    sf::RectangleShape start_line1(sf::Vector2f(vis_scale*2, vis_scale*20));
    start_line1.setFillColor(sf::Color(255, 69, 0));
    start_line1.setPosition(WINDOW_WIDTH/2 - vis_scale*10, WINDOW_HEIGHT/2 - vis_scale*10);
    window_->draw(start_line1);
    sf::RectangleShape start_line2(sf::Vector2f(vis_scale*2, vis_scale*20));
    start_line2.setFillColor(sf::Color(255, 69, 0));
    start_line2.setPosition(WINDOW_WIDTH/2 + vis_scale*10, WINDOW_HEIGHT/2 - vis_scale*10);
    window_->draw(start_line2);
}

void draw_robot(std::shared_ptr<Robot> robot) {
    sf::Sprite sprite(robot_texture);
    sprite.setScale(vis_scale*robot->width_/50.0, vis_scale*robot->length_/50.0);
    double shift_magnitude = vis_scale*sqrt(pow(robot->width_/2, 2) + pow(robot->length_/2, 2));
    double homogenous_x = vis_scale*(robot->x_pos_ - WINDOW_WIDTH/2) + WINDOW_WIDTH/2 + shift_magnitude*cos(robot->angle_ - .75 * M_PI);
    double homogenous_y = vis_scale*(robot->y_pos_ - WINDOW_HEIGHT/2) + WINDOW_HEIGHT/2 + shift_magnitude*sin(robot->angle_ - .75 * M_PI);
    sprite.setPosition(homogenous_x, homogenous_y);
    sprite.setRotation(robot->angle_*180/M_PI);
    window_->draw(sprite);
}	

void update() {
	sf::Event event;
    window_->clear(sf::Color::White); // clear the window with white color
    while (window_->pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed) {
            window_->close();
        } 
    }

    // need to redraw things
    draw_field();
    draw_robot(robot1_);
    draw_robot(robot2_);
    window_->display();
}

int main(int argc, char *argv[]) { // ./sim.sw (r1 x left of 0) (r1 y up of 0) (r1 angle in rad cw) (r2 x right of 0) (r2 y down of 0) (r2 angle in rad cw) (duration for sim: 0 = realtime elapsed)
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ImGui + SFML = <3");
    sf::View view1(sf::Vector2f(100, 100), sf::Vector2f(1280.f, 720.f));
    view1.zoom(0.5); 
    window.setView(view1); 
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    ImGui::GetStyle().ScaleAllSizes(2);
    ImGui::GetIO().FontGlobalScale = 2;
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

	return 0;
}


