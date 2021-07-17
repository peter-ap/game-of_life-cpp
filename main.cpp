#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <unistd.h>

class gameOfLife
{
public:
    int width = 200;
    int height = 200;
    double percent = 0.5;
    cv::Mat old_state = cv::Mat::zeros(height, width, CV_8UC1);
    cv::Mat new_state = cv::Mat::zeros(height, width, CV_8UC1);
    cv::Scalar color_alive = {255, 255, 255};
    cv::Scalar color_dead = {50, 0, 0};
    cv::Mat colored_state = cv::Mat::zeros(height, width, CV_8UC3);
    cv::Mat image = cv::Mat::zeros(height, width, CV_8UC3);

    void initImage()
    {
        int amount = int((width * height) * percent);
        for (int i = 0; i < amount; i++)
        {
            int v = rand() % static_cast<int>(width - 1);
            int u = rand() % static_cast<int>(height - 1);
            old_state.at<uchar>(u, v) = 255;
        }
    }


    void visualise()
    {
        cv::imshow("init", old_state);
        int k = cv::waitKey(0); // Wait for a keystroke in the window
    }

    int alive_neighbours(int u, int v)
    {
        int a_n = 0; // number of alive neighbours
        for (int k = u - 1; k < u + 2; k++)
        {
            for (int l = v - 1; l < v + 2; l++)
            {
                if (k == u && l == v)
                {
                    continue;
                }
                if (k != height && l != width && k > 0 && l > 0)
                {
                    a_n = a_n + int(old_state.at<uchar>(k, l));
                }
                //check if elements are not out of bound!! else loop back around -> grid becomes a toroidal array
                else if (k == height && l != width)
                {
                    // a_n = a_n + int(old_state.at<uchar>(0, l));
                    continue;
                }
                else if (k != height && l == width)
                {
                    // a_n = a_n + int(old_state.at<uchar>(k, 0));
                    continue;
                }
                else
                {
                    // a_n = a_n + int(old_state.at<uchar>(0, 0));
                    continue;
                }
            }
        }
        return a_n / 255;
    }

    void rules_of_life()
    {
        int neighbours = 0;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                neighbours = alive_neighbours(i, j);
                if (int(old_state.at<uchar>(i, j)) == 255)
                {
                    if (neighbours < 2 || neighbours > 3)
                    {
                        new_state.at<uchar>(i, j) = 0;
                    }
                }
                else
                {
                    if (neighbours == 3)
                    {
                        new_state.at<uchar>(i, j) = 255;
                    }
                }
            }
        }
        old_state = new_state.clone();
    }

    void set_color()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (int(old_state.at<uchar>(i, j)) == 255)
                {
                    cv::Range xr(i, i + 1);
                    cv::Range yr(j, j + 1);
                    colored_state(xr, yr) = color_alive;
                }
                else
                {
                    cv::Range xr(i, i + 1);
                    cv::Range yr(j, j + 1);
                    colored_state(xr, yr) = color_dead;
                }
            }
        }
    }

    void play()
    {
        while (true)
        {
            set_color();
            image = colored_state.clone();
            cv::resize(colored_state, image, cv::Size(1000, 1000), 0, 0, cv::INTER_AREA);
            cv::imshow("game of life", image);
            rules_of_life();
            usleep(100);
            if (cv::waitKey(1) == 27)
                break;
        }
        cv::destroyAllWindows();
    }
};

main(int argc, char *argv[])
{
    gameOfLife game;
    game.initImage();
    game.play();
    return 0;
}