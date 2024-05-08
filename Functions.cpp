//菜单、按钮功能实现
#include "pch.h"
#include "Functions.h"

//pic控件初始化
void Init(CWnd* pWnd1, CRect *rect)
{
    rect->SetRect(200, 20, 900, 770);
    pWnd1->MoveWindow(rect->left, rect->top, rect->Width(), rect->Height(), true);
    pWnd1->GetDC()->FillSolidRect(0, 0, rect->Width(), rect->Height(), RGB(200, 200, 200));//相对于rect的原点和长宽
}

//旋转
Mat Rotate(Mat img, double angle)
{
    int w = img.cols;
	int h = img.rows;
    //计算旋转矩阵,逆时针：angle,顺时针：-angle
	Mat rot = getRotationMatrix2D(Point2f(w / 2, h / 2), -angle, 1.0);
	double cos = abs(rot.at<double>(0, 0));
	double sin = abs(rot.at<double>(0, 1));
	int nw = cos * w + sin * h;
	int nh = sin * w + cos * h;
	rot.at<double>(0, 2) += (nw / 2 - w / 2);
	rot.at<double>(1, 2) += (nh / 2 - h / 2);
	warpAffine(img, img, rot, Size(nw, nh), INTER_LINEAR, 0, Scalar(255, 255, 255));
    return img;
}

//保存图片
void SaveImage(Mat img)
{
    CString file_back = "JPG文件(*.JPG)|*.JPG|BMP文件(*.BMP)|*.BMP|PNG文件(*.PNG)|*.PNG|";
    CString name[] = { "jpg","bmp","png" };
    CString filename;

    CFileDialog dlg(FALSE, "jpg", "photo", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, file_back);
    //  文件存盘对话框
    if (dlg.DoModal() == IDOK)
    {
        filename.Format("%s", dlg.GetPathName());
        imwrite(filename.GetBuffer(), img);//当前画面存盘  
    }
}

//灰度图变RGB模式
Mat ToRGB(Mat img_gray)
{
    if (img_gray.channels() == 3)
    {
        AfxMessageBox("已经是彩色图");
        return img_gray;
    }
    Mat img;
    cvtColor(img_gray, img, COLOR_GRAY2RGB);//只是增为三通道，并没有颜色
    imshow("pic", img);

    return img;
}

//RGB模式变灰度图
Mat ToGray(Mat img)
{
    if (img.channels() == 1)
    {
        AfxMessageBox("已经是灰色图");
        return img;
    }
    Mat img_gray;
    cvtColor(img, img_gray, COLOR_RGB2GRAY);
    imshow("pic", img_gray);

    return img_gray;
}

//灰度线性变换
Mat LineTrans(Mat img, float min, float max)
{
    if (img.channels() == 3)
    {
        cvtColor(img, img, COLOR_RGB2GRAY);
    }

    float k = (max - min) / 255;

    // 循环遍历图像的每个像素
    for (int y = 0; y < img.rows; y++) 
    {
        for (int x = 0; x < img.cols; x++) 
        {
            img.at<uchar>(y, x) = saturate_cast<uchar>(k * img.at<uchar>(y, x) + min);//saturate_cast防止颜色溢出
        }
    }

    return img;
}

//灰度分段变换
Mat PartTrans(Mat img, float a1, float b1, float a2, float b2)
{
    if (img.channels() == 3)
    {
        cvtColor(img, img, COLOR_RGB2GRAY);
    }

    float k1 = a1 / a2;
    float k2 = (b2 - b1) / (b1 - a1);
    float k3 = (255 - b2) / (255 - b1);

    // 循环遍历图像的每个像素
    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            if (img.at<uchar>(y, x) < a1)
                img.at<uchar>(y, x) = saturate_cast<uchar>(img.at<uchar>(y, x) * k1);
            else if (img.at<uchar>(y, x) > b1)
                img.at<uchar>(y, x) = saturate_cast<uchar>(img.at<uchar>(y, x) * k3 + 255 - k3 * 255);
            else
                img.at<uchar>(y, x) = saturate_cast<uchar>(img.at<uchar>(y, x) * k2 + a2 - k2 * a1);
        }
    }

    return img;
}

//灰度对数变换
Mat LogTrans(Mat img, float a, float b, float c)
{
    if (img.channels() == 3)
    {
        cvtColor(img, img, COLOR_RGB2GRAY);
    }

    // 循环遍历图像的每个像素
    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            img.at<uchar>(y, x) = saturate_cast<uchar>((log((double)(img.at<uchar>(y, x) + 1))) / (b * log(c)) + a + 0.5);
        }
    }

    return img;
}

//直方图均衡化
void Show_Histogram(Mat img, String name)
{
    if (img.channels() == 3)
    {
        cvtColor(img, img, COLOR_RGB2GRAY);
    }

    Mat hist;
    int histSize = 256;  // 直方图尺寸
    float range[] = { 0, 256 };  // 像素灰度值范围
    const float* histRange = { range };
    calcHist(&img, 1, 0, Mat(), hist, 1, &histSize, &histRange, true, false);//统计

    // 绘制直方图
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());//归一化

    for (int i = 1; i < histSize; i++) 
    {
        //绘制图像
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
            Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
            Scalar(0, 0, 255), 2, LINE_AA);
    }

    namedWindow(name);
    imshow(name, histImage);
}

//直方图规格化
Mat Histogram_Match(Mat img1, Mat img2)
{
    if (img1.channels() == 3)
    {
        cvtColor(img1, img1, COLOR_RGB2GRAY);
    }
    if (img2.channels() == 3)
    {
        cvtColor(img2, img2, COLOR_RGB2GRAY);
    }

    equalizeHist(img1, img1);
    equalizeHist(img2, img2);

    Mat hist1;
    Mat hist2;
    int histSize = 256;  // 直方图尺寸
    float range[] = { 0, 256 };  // 像素灰度值范围
    const float* histRange = { range };
    calcHist(&img1, 1, 0, Mat(), hist1, 1, &histSize, &histRange, true, false);//统计
    calcHist(&img2, 1, 0, Mat(), hist2, 1, &histSize, &histRange, true, false);//统计

    //计算两个均衡化图像直方图的累积概率
    float hist1_cdf[256] = { hist1.at<float>(0) };
    float hist2_cdf[256] = { hist2.at<float>(0) };
    for (int i = 1; i < 256; i++)
    {
        hist1_cdf[i] = (hist1_cdf[i - 1] + hist1.at<float>(i));
        hist2_cdf[i] = (hist2_cdf[i - 1] + hist2.at<float>(i));
    }

    for (int i = 0; i < 256; i++)
    {
        hist1_cdf[i] = hist1_cdf[i] / (img1.rows * img1.cols);
        hist2_cdf[i] = hist2_cdf[i] / (img2.rows * img2.cols);
    }

    // 两个累计概率之间的差值，用于找到最接近的点
    float diff_cdf[256][256];
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++)
        {
            diff_cdf[i][j] = fabs(hist1_cdf[i] - hist2_cdf[j]);
        }
    }

    Mat lut(1, 256, CV_8U);
    for (int i = 0; i < 256; i++)
    {
        //查找源灰度级为i的映射灰度和i的累积概率差最小(灰度接近)的规定化灰度
        float min = diff_cdf[i][0];
        int index = 0;
        for (int j = 0; j < 256; j++) {
            if (min > diff_cdf[i][j]) {
                min = diff_cdf[i][j];
                index = j;
            }
        }
        lut.at<uchar>(i) = index;
    }
    LUT(img1, lut, img1);

    return img1;
}

//添加椒盐噪声，n=噪声点数量
Mat Add_Saltpepper(Mat img, int n)
{
    int x, y, wb;
    for (int i = 0; i < n ; ++i)
    {
        //产生随机整数
        x = cvflann::rand_int() % (img.cols);
        y = cvflann::rand_int() % (img.rows);
        wb = cvflann::rand_int() % 2;

        if (wb == 0)//添加白噪声
        {
            if (img.channels() == 1)
            {
                img.at<uchar>(y, x) = 255;
            }
            else if (img.channels() == 3)
            {
                img.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
            }
        }
        else//添加黑噪声
        {
            if (img.channels() == 1)
            {
                img.at<uchar>(y, x) = 0;
            }
            else if (img.channels() == 3)
            {
                img.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
            }
        }
    }

    return img;
}

//添加高斯噪声，a、b是生成高斯噪声的均值和标准差
Mat Add_Gaussian(Mat img, int a, int b)
{
    Mat noise = cv::Mat::zeros(img.size(), img.type());
    RNG rng;
    rng.fill(noise, RNG::NORMAL, a, b);//生成随机噪声
    return img + noise;//将噪声加入原图像
}

//低通滤波
Mat ILPF(Mat img)
{
    if (img.channels() == 3)
    {
        cvtColor(img, img, COLOR_RGB2GRAY);
    }
    img.convertTo(img, CV_32F);
    Mat planes[] = { img,Mat::zeros(img.size(),CV_32F) };
    Mat DFT_image;
    merge(planes, 2, DFT_image);
    dft(DFT_image, DFT_image);
    
    Mat H(img.size(),CV_32F,Scalar(1));
    double D=0;
    double D0= 0.1 * std::min(img.rows, img.cols);
    for (int u=0;u<H.rows;u++) {
        for (int v=0;v<H.cols;v++) {
            D=sqrt((u-img.rows/2)*(u-img.rows/2)+(v-img.cols/2)*(v-img.cols/2));
            if(D>D0)
            {
                H.at<float>(u,v)=0;
            }
        }
    }

    // 重新排列傅里叶图像中的象限，使原点位于图像中心
    int cx = H.cols / 2;
    int cy = H.rows / 2;
    Mat q0(H, Rect(0, 0, cx, cy));   // 左上区域
    Mat q1(H, Rect(cx, 0, cx, cy));  // 右上区域
    Mat q2(H, Rect(0, cy, cx, cy));  // 左下区域
    Mat q3(H, Rect(cx, cy, cx, cy)); // 右下区域

    //交换象限中心化
    Mat tmp;
    q0.copyTo(tmp); q3.copyTo(q0); tmp.copyTo(q3);//左上与右下进行交换
    q1.copyTo(tmp); q2.copyTo(q1); tmp.copyTo(q2);//右上与左下进行交换
    
    Mat planesH[] = { Mat_<float>(H.clone()),Mat_<float>(H.clone()) };
    Mat planes_dft[] = { DFT_image,Mat::zeros(DFT_image.size(),CV_32F) };
    split(DFT_image, planes_dft);
    Mat planes_out[] = { Mat::zeros(DFT_image.size(),CV_32F),Mat::zeros(DFT_image.size(),CV_32F) };
    planes_out[0] = planesH[0].mul(planes_dft[0]);
    planes_out[1] = planesH[1].mul(planes_dft[1]);
    Mat complexIH;
    merge(planes_out,2,complexIH);
    
    //IDFT
    Mat imgOut;
    dft(complexIH, imgOut, DFT_INVERSE | DFT_REAL_OUTPUT);//傅里叶逆变换
    normalize(imgOut, imgOut, 0, 1, NORM_MINMAX);//归一化
    imgOut.convertTo(imgOut, CV_8U, 255, 0);

    return imgOut;
}

//图像拼接
Mat Add_Photo(Mat img1, Mat img2, int a)
{
    int width = 0, height = 0;
    if (a == 0)//横
    {
        resize(img2, img2, Size(img2.cols * img1.rows / img2.rows, img1.rows));
        height = img1.rows;
        width =  img1.cols + img2.cols + 10;
    }
    else if (a == 1)//纵
    {
        resize(img2, img2, Size(img1.cols, img2.rows * img1.cols / img2.cols));
        height = img1.rows + img2.rows + 10;
        width = img1.cols;
    }
    
    Mat img(Size(width + 1, height + 1), CV_8UC3, Scalar(255, 255, 255));
    img1.convertTo(img1, img.type());
    img2.convertTo(img2, img.type());
    
    img1.copyTo(img(Rect(0, 0, img1.cols, img1.rows)));//注意col和row的顺序
    if (a == 0)
        img2.copyTo(img(Rect(img1.cols + 9, 0, img2.cols, img2.rows)));
    else if (a == 1)
        img2.copyTo(img(Rect(0, img1.rows + 9, img2.cols, img2.rows)));
    
    return img;
}

//线条化
Mat To_Line(Mat img)
{
    if (img.channels() == 3)
    {
        cvtColor(img, img, COLOR_RGB2GRAY);
    }
    //处理过程中的第一、第二个阈值
    Canny(img, img, 50, 150);

    return img;
}

//颗粒效果
Mat Add_Grain(Mat img,int rank)
{
    int tip = 1;
    if (img.channels() == 3)
        tip = 3;

    for (int i = 0; i < img.rows; ++i)
    {
        uchar* t = img.ptr<uchar>(i);//图像行指针
        for (int j = 0; j < tip * img.cols; ++j)//
        {
            int temp = t[j];
            temp += ((rand() % (2 * rank)) - rank);
            if (temp < 0)temp = 0;
            if (temp > 255)temp = 255;
            t[j] = temp;
        }
    }
    return img;
}

//反色
Mat Inverted_Color(Mat img)
{
    int tip = 1;
    if (img.channels() == 3)
        tip = 3;

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols * tip; j++)
        {
            img.at<uchar>(i, j) = 255 - img.at<uchar>(i, j);   //对每一个像素反转
        }
    }
    return img;
}

//浮雕
Mat Photo_Relief(Mat img)
{
    if (img.channels() == 1)
    {
        cvtColor(img, img, COLOR_GRAY2RGB);
    }

    Mat temp = img.clone();
    for (int i = 1; i < img.rows - 1; ++i)
    {
        uchar* s1 = img.ptr<uchar>(i - 1);
        uchar* s2 = img.ptr<uchar>(i + 1);
        uchar* t = temp.ptr<uchar>(i);
        for (int j = 1; j < img.cols - 1; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                t[3 * j + k] = saturate_cast<uchar>(s1[3 * (j - 1) + k] - s2[3 * (j + 1) + k] + 128);
            }
        }
    }
    return temp;
}

//水中倒影
Mat InWater(Mat img)
{
    Mat img2;
    flip(img, img2, 0);//上下镜像
    srand((unsigned)time(0));
    for (int i= 0; i != img2.rows; ++i)//每个像素点在原来的位置周围随机振荡
    {
        for (int j = 0; j < img2.cols; ++j)
        {
            int deltax = rand() % 25;//震荡半径为25
            while (j + deltax >= img2.cols)
            {
                deltax = rand() % 25;
            }
            img2.at<Vec3b>(i, j) = img2.at<Vec3b>(i, j + deltax);
        }
    }
    medianBlur(img2, img2, 3);//中值滤波

    Mat w = imread("water.png");//水波图片
    resize(w, w, img.size());
    addWeighted(w, 0.25, img2, 0.75, 0, img2);

    Mat result = cv::Mat::zeros(Size(img.cols, img.rows * 2), img.type());
    img.copyTo(result(Rect(0, 0, img.cols, img.rows)));
    img2.copyTo(result(Rect(0, img.rows, img.cols, img.rows)));
    return result;
}