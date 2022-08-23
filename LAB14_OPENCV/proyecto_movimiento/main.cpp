#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
using namespace cv;
using namespace std;

int num_color(int H, int S, int V)
{
    if (V < 70)
        return 1; // "negro";
    else if (S < 35)
        return 0; // "blanco";
    else if (H < 10 || H > 160)
        return 2; // "rojo";
    else if (H >= 10 && H < 25)
        return 3; // "naranja";
    else if (H >= 25 && H < 35)
        return 4; // "amarillo";
    else if (H >= 35 && H < 75)
        return 5; // "verde";
    else if (H >= 75 && H < 100)
        return 6; // "celeste";
    else if (H >= 100 && H < 130)
        return 7; // "azul";
    else if (H >= 130 && H <= 160)
        return 8; // "violeta";
}

string str_color(int indice)
{
    if (indice == 0)
        return "blanco";
    else if (indice == 1)
        return "negro";
    else if (indice == 2)
        return "rojo";
    else if (indice == 3)
        return "naranja";
    else if (indice == 4)
        return "amarillo";
    else if (indice == 5)
        return "verde";
    else if (indice == 6)
        return "celeste";
    else if (indice == 7)
        return "azul";
    else if (indice == 8)
        return "violeta";
}

int main(int argc, char* argv[])
{
    Ptr<BackgroundSubtractor> knn = createBackgroundSubtractorKNN(500,400.0,false);
    Mat frame, fgMask_knn, erosion_dst, dilation_dst, frameHSV;
    //VideoCapture capture("http://68.116.51.74/mjpg/video.mjpg");
    VideoCapture capture("C://Users//Administrador//Documents//ComputacionGrafica//Open_CV//src//proyecto_movimiento//camara_trafico_2.mp4");


    // error abriendo el video 
    if (!capture.isOpened()) {
        cout << "unable to open capture";
        return 0;
    }
    while (true) {
        capture >> frame;
        if (frame.empty())
            break;

        // Substraccion de fondo con metodo KNN
        resize(frame, frame, cv::Size(400, 300));
        knn->apply(frame, fgMask_knn);

        // Erosion para reducir el ruido
        Mat element = getStructuringElement(MORPH_RECT, Size(4, 4), Point(-1,-1));
        erode(fgMask_knn, erosion_dst, element);

        // Aplicando 'cierre' para definir las formas
        Mat element2 = getStructuringElement(MORPH_RECT, Size(8, 8), Point(-1, -1));
        dilate(erosion_dst, dilation_dst, element2);
        erode(dilation_dst, dilation_dst, element);

        // Dibujo del contorno de las formas generadas
        vector<vector<Point>> contours;
        vector<Point> contorno_suave;
        findContours(dilation_dst, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        //drawContours(frame, contours, -1, (0,0,255), 1); // dibuja los contornos sobre el frame
       
        for (int i = 0; i < contours.size(); i++) {
            double area = contourArea(contours[i]);

            if (area > 40) { // unidades de area detectables para enmarcar 
                convexHull(contours[i], contorno_suave); // suaviza el contorno 
                
                // dibuja el contorno rectangular
                Rect bound = boundingRect(contorno_suave);  
                rectangle(frame, bound, Scalar(0,255,0), 1);

                // detectar color principal (moda) dentro de cada recuadro
                cvtColor(frame, frameHSV, COLOR_BGR2HSV);
                
                vector<int> cont_colores(9,0);
                int pos, h, s, v, x_ini, y_ini, x_fin, y_fin; 
                x_ini = bound.x;
                y_ini = bound.y;
                x_fin = x_ini + bound.width;
                y_fin = y_ini + bound.height;
                

                for (int i = y_ini; i < y_fin; i++)
                {
                    for (int j = x_ini; j < x_fin; j++)
                    {
                        h = frameHSV.at<Vec3b>(i, j)[0];
                        s = frameHSV.at<Vec3b>(i, j)[1];
                        v = frameHSV.at<Vec3b>(i, j)[2];

                        pos = num_color(h, s, v);
                        cont_colores[pos]++;
                    }
                }

                int max = 0, ind = 0; 
                for (int i = 0; i < cont_colores.size(); i++)
                {
                    if (cont_colores[i] > max)
                    {
                        max = cont_colores[i];
                        ind = i; 
                    }
                }
                // marcar el recuadro con una etiqueta de su color
                string color_ = str_color(ind);
                putText(frame, color_, Point2f(bound.x, bound.y), FONT_HERSHEY_PLAIN, 1, Scalar(0,255,0), 1);
                
                //cont_colores.clear();
                for (int i = 0; i < cont_colores.size(); i++)
                    cont_colores[i] = 0;
            }
        }

        // mostrar las ventanas 
        imshow("Frame", frame);
        imshow("knn", fgMask_knn);
        imshow("erosion", erosion_dst);
        imshow("dilatacion", dilation_dst);
        imshow("frameHSV", frameHSV);
        
        // salida por teclado
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
            break;
    }
    return 0;
}