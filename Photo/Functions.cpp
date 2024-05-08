//�˵�����ť����ʵ��
#include "pch.h"
#include "Functions.h"

//pic�ؼ���ʼ��
void Init(CWnd* pWnd1, CRect *rect)
{
    rect->SetRect(200, 20, 900, 770);
    pWnd1->MoveWindow(rect->left, rect->top, rect->Width(), rect->Height(), true);
    pWnd1->GetDC()->FillSolidRect(0, 0, rect->Width(), rect->Height(), RGB(200, 200, 200));//�����rect��ԭ��ͳ���
}

//��ת
Mat Rotate(Mat img, double angle)
{
    int w = img.cols;
	int h = img.rows;
    //������ת����,��ʱ�룺angle,˳ʱ�룺-angle
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

//����ͼƬ
void SaveImage(Mat img)
{
    CString file_back = "JPG�ļ�(*.JPG)|*.JPG|BMP�ļ�(*.BMP)|*.BMP|PNG�ļ�(*.PNG)|*.PNG|";
    CString name[] = { "jpg","bmp","png" };
    CString filename;

    CFileDialog dlg(FALSE, "jpg", "photo", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, file_back);
    //  �ļ����̶Ի���
    if (dlg.DoModal() == IDOK)
    {
        filename.Format("%s", dlg.GetPathName());
        imwrite(filename.GetBuffer(), img);//��ǰ�������  
    }
}

//�Ҷ�ͼ��RGBģʽ
Mat ToRGB(Mat img_gray)
{
    if (img_gray.channels() == 3)
    {
        AfxMessageBox("�Ѿ��ǲ�ɫͼ");
        return img_gray;
    }
    Mat img;
    cvtColor(img_gray, img, COLOR_GRAY2RGB);//ֻ����Ϊ��ͨ������û����ɫ
    imshow("pic", img);

    return img;
}

//RGBģʽ��Ҷ�ͼ
Mat ToGray(Mat img)
{
    if (img.channels() == 1)
    {
        AfxMessageBox("�Ѿ��ǻ�ɫͼ");
        return img;
    }
    Mat img_gray;
    cvtColor(img, img_gray, COLOR_RGB2GRAY);
    imshow("pic", img_gray);

    return img_gray;
}

//�Ҷ����Ա任
Mat LineTrans(Mat img, float min, float max)
{
    if (img.channels() == 3)
    {
        cvtColor(img, img, COLOR_RGB2GRAY);
    }

    float k = (max - min) / 255;

    // ѭ������ͼ���ÿ������
    for (int y = 0; y < img.rows; y++) 
    {
        for (int x = 0; x < img.cols; x++) 
        {
            img.at<uchar>(y, x) = saturate_cast<uchar>(k * img.at<uchar>(y, x) + min);//saturate_cast��ֹ��ɫ���
        }
    }

    return img;
}

//�Ҷȷֶα任
Mat PartTrans(Mat img, float a1, float b1, float a2, float b2)
{
    if (img.channels() == 3)
    {
        cvtColor(img, img, COLOR_RGB2GRAY);
    }

    float k1 = a1 / a2;
    float k2 = (b2 - b1) / (b1 - a1);
    float k3 = (255 - b2) / (255 - b1);

    // ѭ������ͼ���ÿ������
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

//�Ҷȶ����任
Mat LogTrans(Mat img, float a, float b, float c)
{
    if (img.channels() == 3)
    {
        cvtColor(img, img, COLOR_RGB2GRAY);
    }

    // ѭ������ͼ���ÿ������
    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            img.at<uchar>(y, x) = saturate_cast<uchar>((log((double)(img.at<uchar>(y, x) + 1))) / (b * log(c)) + a + 0.5);
        }
    }

    return img;
}

//ֱ��ͼ���⻯
void Show_Histogram(Mat img, String name)
{
    if (img.channels() == 3)
    {
        cvtColor(img, img, COLOR_RGB2GRAY);
    }

    Mat hist;
    int histSize = 256;  // ֱ��ͼ�ߴ�
    float range[] = { 0, 256 };  // ���ػҶ�ֵ��Χ
    const float* histRange = { range };
    calcHist(&img, 1, 0, Mat(), hist, 1, &histSize, &histRange, true, false);//ͳ��

    // ����ֱ��ͼ
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());//��һ��

    for (int i = 1; i < histSize; i++) 
    {
        //����ͼ��
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
            Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
            Scalar(0, 0, 255), 2, LINE_AA);
    }

    namedWindow(name);
    imshow(name, histImage);
}

//ֱ��ͼ���
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
    int histSize = 256;  // ֱ��ͼ�ߴ�
    float range[] = { 0, 256 };  // ���ػҶ�ֵ��Χ
    const float* histRange = { range };
    calcHist(&img1, 1, 0, Mat(), hist1, 1, &histSize, &histRange, true, false);//ͳ��
    calcHist(&img2, 1, 0, Mat(), hist2, 1, &histSize, &histRange, true, false);//ͳ��

    //�����������⻯ͼ��ֱ��ͼ���ۻ�����
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

    // �����ۼƸ���֮��Ĳ�ֵ�������ҵ���ӽ��ĵ�
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
        //����Դ�Ҷȼ�Ϊi��ӳ��ҶȺ�i���ۻ����ʲ���С(�ҶȽӽ�)�Ĺ涨���Ҷ�
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

//��ӽ���������n=����������
Mat Add_Saltpepper(Mat img, int n)
{
    int x, y, wb;
    for (int i = 0; i < n ; ++i)
    {
        //�����������
        x = cvflann::rand_int() % (img.cols);
        y = cvflann::rand_int() % (img.rows);
        wb = cvflann::rand_int() % 2;

        if (wb == 0)//��Ӱ�����
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
        else//��Ӻ�����
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

//��Ӹ�˹������a��b�����ɸ�˹�����ľ�ֵ�ͱ�׼��
Mat Add_Gaussian(Mat img, int a, int b)
{
    Mat noise = cv::Mat::zeros(img.size(), img.type());
    RNG rng;
    rng.fill(noise, RNG::NORMAL, a, b);//�����������
    return img + noise;//����������ԭͼ��
}

//��ͨ�˲�
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

    // �������и���Ҷͼ���е����ޣ�ʹԭ��λ��ͼ������
    int cx = H.cols / 2;
    int cy = H.rows / 2;
    Mat q0(H, Rect(0, 0, cx, cy));   // ��������
    Mat q1(H, Rect(cx, 0, cx, cy));  // ��������
    Mat q2(H, Rect(0, cy, cx, cy));  // ��������
    Mat q3(H, Rect(cx, cy, cx, cy)); // ��������

    //�����������Ļ�
    Mat tmp;
    q0.copyTo(tmp); q3.copyTo(q0); tmp.copyTo(q3);//���������½��н���
    q1.copyTo(tmp); q2.copyTo(q1); tmp.copyTo(q2);//���������½��н���
    
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
    dft(complexIH, imgOut, DFT_INVERSE | DFT_REAL_OUTPUT);//����Ҷ��任
    normalize(imgOut, imgOut, 0, 1, NORM_MINMAX);//��һ��
    imgOut.convertTo(imgOut, CV_8U, 255, 0);

    return imgOut;
}

//ͼ��ƴ��
Mat Add_Photo(Mat img1, Mat img2, int a)
{
    int width = 0, height = 0;
    if (a == 0)//��
    {
        resize(img2, img2, Size(img2.cols * img1.rows / img2.rows, img1.rows));
        height = img1.rows;
        width =  img1.cols + img2.cols + 10;
    }
    else if (a == 1)//��
    {
        resize(img2, img2, Size(img1.cols, img2.rows * img1.cols / img2.cols));
        height = img1.rows + img2.rows + 10;
        width = img1.cols;
    }
    
    Mat img(Size(width + 1, height + 1), CV_8UC3, Scalar(255, 255, 255));
    img1.convertTo(img1, img.type());
    img2.convertTo(img2, img.type());
    
    img1.copyTo(img(Rect(0, 0, img1.cols, img1.rows)));//ע��col��row��˳��
    if (a == 0)
        img2.copyTo(img(Rect(img1.cols + 9, 0, img2.cols, img2.rows)));
    else if (a == 1)
        img2.copyTo(img(Rect(0, img1.rows + 9, img2.cols, img2.rows)));
    
    return img;
}

//������
Mat To_Line(Mat img)
{
    if (img.channels() == 3)
    {
        cvtColor(img, img, COLOR_RGB2GRAY);
    }
    //��������еĵ�һ���ڶ�����ֵ
    Canny(img, img, 50, 150);

    return img;
}

//����Ч��
Mat Add_Grain(Mat img,int rank)
{
    int tip = 1;
    if (img.channels() == 3)
        tip = 3;

    for (int i = 0; i < img.rows; ++i)
    {
        uchar* t = img.ptr<uchar>(i);//ͼ����ָ��
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

//��ɫ
Mat Inverted_Color(Mat img)
{
    int tip = 1;
    if (img.channels() == 3)
        tip = 3;

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols * tip; j++)
        {
            img.at<uchar>(i, j) = 255 - img.at<uchar>(i, j);   //��ÿһ�����ط�ת
        }
    }
    return img;
}

//����
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

//ˮ�е�Ӱ
Mat InWater(Mat img)
{
    Mat img2;
    flip(img, img2, 0);//���¾���
    srand((unsigned)time(0));
    for (int i= 0; i != img2.rows; ++i)//ÿ�����ص���ԭ����λ����Χ�����
    {
        for (int j = 0; j < img2.cols; ++j)
        {
            int deltax = rand() % 25;//�𵴰뾶Ϊ25
            while (j + deltax >= img2.cols)
            {
                deltax = rand() % 25;
            }
            img2.at<Vec3b>(i, j) = img2.at<Vec3b>(i, j + deltax);
        }
    }
    medianBlur(img2, img2, 3);//��ֵ�˲�

    Mat w = imread("water.png");//ˮ��ͼƬ
    resize(w, w, img.size());
    addWeighted(w, 0.25, img2, 0.75, 0, img2);

    Mat result = cv::Mat::zeros(Size(img.cols, img.rows * 2), img.type());
    img.copyTo(result(Rect(0, 0, img.cols, img.rows)));
    img2.copyTo(result(Rect(0, img.rows, img.cols, img.rows)));
    return result;
}