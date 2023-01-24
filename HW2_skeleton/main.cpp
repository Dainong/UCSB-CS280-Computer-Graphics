#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;
Eigen::Matrix4f get_rotation(Eigen::Vector3f axis, float angle);

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1,
        -eye_pos[2], 0, 0, 0, 1;

    view = translate * view;

    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    rotation_angle = rotation_angle * MY_PI / 180;
    model <<
        cos(rotation_angle), -sin(rotation_angle), 0.0, 0.0,
        sin(rotation_angle),  cos(rotation_angle), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0;
    return model;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f perspective = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f scaling = Eigen::Matrix4f::Identity();
    // TODO: Implement this function
    float top    = tan(eye_fov * MY_PI / 360) * zNear;
    float bottom = -1 * top; 
    float right  = top * aspect_ratio;
    float left   = -1 * right;
    float n      = -1 * zNear;
    float f      = -1 * zFar;
    perspective <<
        n, 0.0, 0.0, 0.0,
        0.0,  n, 0.0, 0.0,
        0.0, 0.0, n + f, -1 * n * f,
        0.0, 0.0, 1.0, 0.0;

    scaling <<
        2 / (right - left), 0, 0, 0,
        0, 2 / (top - bottom), 0, 0,
        0, 0, 2 / (n - f), 0,
        0, 0, 0, 1;

    translation <<
        1, 0, 0, -1 * (right + left) / 2,
        0, 1, 0, -1 * (top + bottom) / 2,
        0, 0, 1, -1 * (n + f) / 2,
        0, 0, 0, 1;

    projection = scaling * translation * perspective;
    return projection;
}

// Bonus function ------------------------------------------------
Eigen::Matrix4f get_rotation(Eigen::Vector3f axis, float angle) {
    Eigen::Matrix4f rotation = Eigen::Matrix4f::Identity();
    Eigen::Matrix3f tmp = Eigen::Matrix3f::Identity();
    Eigen::Matrix3f I = Eigen::Matrix3f::Identity();
    Eigen::Matrix3f nnT = Eigen::Matrix3f::Identity();

    axis.normalize();

    float nx = axis[0];
    float ny = axis[1];
    float nz = axis[2];
    tmp << 
        0, -1 * nz, ny,
        nz, 0, -1 * nx,
        -1 * ny, nx, 0;

    nnT = axis * axis.transpose();
    tmp = cos(angle * MY_PI / 180) * I + (1 - cos(angle * MY_PI / 180)) * nnT + sin(angle * MY_PI / 180) * tmp;
    rotation.topLeftCorner(3, 3) = tmp;
    return rotation;
}
// Bonus function -----------------------------------------------

int main(int argc, const char** argv)
{
    // Bonus: axis initialize------------------------------------
    Eigen::Vector3f axis;
    axis <<
        0.0, 0.0, 3.0; 
    // Bonus ----------------------------------------------------
    float angle = 0;
    bool command_line = false;
    std::string filename = "output.png";

    if (argc >= 3) {
        command_line = true;
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
        else
            return 0;
    }

    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0, 0, 5};

    std::vector<Eigen::Vector3f> pos{{1, 0, -2}, {0, 2, -3}, {-2, 0, -2}};

    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);

    int key = 0;
    int frame_count = 0;

    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        //r.set_model(get_rotation(axis, angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;
    }

    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);
        
        // Bonus function
        //r.set_model(get_rotation(axis, angle));

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';

        if (key == 'a') {
            angle += 10;
        }
        else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;
}
