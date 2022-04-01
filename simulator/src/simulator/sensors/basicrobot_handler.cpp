#include <simulator/sensors/basicrobot_handler.h>

BasicRobotHandler::BasicRobotHandler(std::shared_ptr<Robot> r, std::shared_ptr<Robot> o) {
    robot_ = r;
    opponent_ = o;
    dist_ = std::vector<std::shared_ptr<DistanceSensorJ>>();

    // these should be the right positions but i havent done the cones yet
    dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_/2, 0, 0*M_PI/180, 3.6*M_PI/180, 150));
    dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_/2, r->length_, 180*M_PI/180, 3.6*M_PI/180, 150));
    dist_.push_back(std::make_shared<DistanceSensorJ>(r, 0, r->length_/2, -90*M_PI/180, 3.6*M_PI/180, 150));
    dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_, r->length_/2, 270*M_PI/180, 3.6*M_PI/180, 150));

    // i dont think we need the extra parameters, just leave it liek this for now in case stuff breaks
    gps_.push_back(std::make_shared<GPSSensor>(r, r->width_/2, r->length_/2));

    // dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_/2 - 3, r->length_/2, -10*M_PI/180, 3.6*M_PI/180, 150));
    // dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_/2 - 3, r->length_/4, -5*M_PI/180, 3.6*M_PI/180, 150));
    // dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_/2 - 3, r->length_/8, 0, 3.6*M_PI/180, 150));
    // dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_/2 - 3, -r->length_/8, 0, 3.6*M_PI/180, 150));
    // dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_/2 - 3, -r->length_/4, 5*M_PI/180, 3.6*M_PI/180, 150));
    // dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_/2 - 3, -r->length_/2, 10*M_PI/180, 3.6*M_PI/180, 150));
    imu_ = std::make_shared<IMU>(r);
    line_ = std::vector<std::shared_ptr<LineSensor>>();
    line_.push_back(std::make_shared<LineSensor>(r, r->width_/2, 0, 200, r->width_/2, r->length_/2));
    line_.push_back(std::make_shared<LineSensor>(r, r->width_/2, r->length_, 200, r->width_/2, -r->length_/2));    
    enc_ = std::vector<std::shared_ptr<Encoder>>();
    enc_.push_back(std::make_shared<Encoder>(r, 500, true));
    enc_.push_back(std::make_shared<Encoder>(r, 500, false));
    // gps stuff here
}

SensorData BasicRobotHandler::read(double duration) {
    SensorData s;
    auto imu_readings = imu_->read(duration);
    s.x_accel_ = imu_readings[0];
    s.y_accel_ = imu_readings[1];
    s.z_gyro_ = imu_readings[2];
    auto d_buff = std::vector<double>();
    for (std::shared_ptr<DistanceSensorJ> d : dist_) {
        d_buff.push_back(d->read(opponent_));
    }
    s.dist_buffer_ = d_buff;
    auto l_buff = std::vector<int>();
    for (std::shared_ptr<LineSensor> l : line_) {
        l_buff.push_back(l->read());
    }
    s.line_buffer_ = l_buff;
    auto e_buff = std::vector<int>();
    for (std::shared_ptr<Encoder> e : enc_) {
        e_buff.push_back(e->read(duration));
    }
    auto g_buff = std::vector<int>();
    for (std::shared_ptr<GPSSensor> g : gps_) {
        g_buff.push_back(g->get_x_pos());
        g_buff.push_back(g->get_y_pos());

    }
    s.encoder_buffer_ = e_buff;
    return s;
}