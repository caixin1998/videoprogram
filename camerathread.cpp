#include "camerathread.h"
#include<cv.h>

extern string childid;
CameraThread::CameraThread(QObject *parent) : QObject(parent)
{
    
    
    index = 0;
	mark  = 0;
	//outDir = "D:\\Qtopencv\\output\\";
    //start();
	//capture.open(0);
 
}

void CameraThread::start()
{
   //if (capture.isOpened())
   //     capture.release(); 

   // capture.open("D:/chrome_download/SampleVideo2.mp4"); 
	capture.open(0);
	while(!capture.isOpened())
		capture.open(0);
    if (capture.isOpened())
    {
        rate= capture.get(CV_CAP_PROP_FPS);
        capture >> frame;
         if (!frame.empty())
        {
            image = Mat2QImage(frame);
               //set timer match with FPS
            connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
			connect(timer, SIGNAL(timeout()), this, SLOT(record_camera()));
        }

    }
    
}

void CameraThread::start_record()
{
   // connect(timer, SIGNAL(timeout()), this, SLOT(record_camera()));
   mark =1;
}

void CameraThread::stop_record()
{
  //  disconnect(timer, SIGNAL(timeout()), this, SLOT(record_camera()));
  mark = 0;
}

void CameraThread::record_camera()
{
    if(mark==1)
    {
        outDir = ".\\output\\"+childid+"\\";
        std::string str;
        str = outDir + std::to_string(index++) +".jpg";
	    std::cout << str+"\n";
        Mat outMat;
        cvtColor(frame, outMat, CV_BGR2RGB);
	    imwrite(str, outMat);

    }

	
}

void CameraThread::play_video()
{
	
    emit showImage(image);
}

void CameraThread::start_play()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(play_video()));
}

void CameraThread::stop_play()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(play_video()));
}


QImage  CameraThread::Mat2QImage(cv::Mat cvImg)
{
	QImage qImg;
	if (cvImg.channels() == 3)                          
	{
		cvtColor(cvImg, cvImg, CV_BGR2RGB);
		qImg = QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_RGB888);
	}
	else if (cvImg.channels() == 1)                    
	{
		qImg = QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_Indexed8);
	}
	else
	{
		qImg = QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_RGB888);
	}
 
	return qImg;

}

void CameraThread::nextFrame()
{
    capture >> frame;
    if (!frame.empty())
    {
        image = Mat2QImage(frame);
        //this->update();
    }

}