//slider�ؼ�����ʵ��
#include "pch.h"
#include "SliderSet.h"

//����
Mat Zoom(Mat img, double size)
{
    //��ֵ��
    //�Ͽ췽����INTER_NEAREST = 0��INTER_LINEAR = 1
    //����������INTER_CUBIC = 2��INTER_LANCZOS4 = 3
    resize(img, img, Size(), 1 + size / 100, 1 + size / 100, INTER_NEAREST);
    imshow("pic", img);
    return img;
}

//���ȺͶԱȶ�
Mat Bright_Contrast(Mat img, int B, float C)
{
    Mat img2;
    img.copyTo(img2);
    for (int i = 1; i < img.rows; i++)
    {
        for (int j = 1; j < img.cols; j++)
        {
            if (img2.channels() == 3)
            {
                //��ȡͨ��������ֵ
                Vec3b x = img.at<Vec3b>(i, j);
                float b = x[0];
                float g = x[1];
                float r = x[2];
                //�޸�ͨ��������ֵ
                img2.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(b * (1 + C / 100) + B);
                img2.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(g * (1 + C / 100) + B);
                img2.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(r * (1 + C / 100) + B);
            }
            else if (img2.channels() == 1)
            {
                //�޸�ͨ��������ֵ
                img2.at<uchar>(i, j) = saturate_cast<uchar>(img.at<uchar>(i, j) * (1 + C / 100) + B);
            }
        }
    }
    imshow("pic", img2);
    return img2;
}

// ���Ͷ�
Mat Saturation(Mat img, float saturation)
{
	if (img.channels() == 1)
	{
		AfxMessageBox("��ͼ��Ϊ�Ҷ�ͼ");
		return img;
	}
    float Increment = saturation / 100;
    Mat img2 = img.clone();
	for (int i = 0; i < img.rows; ++i)
	{
		uchar* t = img2.ptr<uchar>(i);
		uchar* s = img.ptr<uchar>(i);
		for (int j = 0; j < img.cols; ++j)
		{
			float max = s[3 * j];
			float min = s[3 * j];
			for (int k = 1; k < 3; ++k)
			{
				if (max < s[3 * j + k])max = s[3 * j + k];
				if (min > s[3 * j + k])min = s[3 * j + k];
			}

			uchar b = s[3 * j];
			uchar g = s[3 * j + 1];
			uchar r = s[3 * j + 2];
			
			float delta, value;
			float L, S, alpha;
			delta = (max - min) / 255;
			if (delta == 0)
				continue;
			value = (max + min) / 255;
			L = value / 2;
			if (L < 0.5)
				S = delta / value;
			else
				S = delta / (2 - value);
			if (Increment >= 0)
			{
				if ((Increment + S) >= 1)
					alpha = S;
				else
					alpha = 1 - Increment;
				alpha = 1 / alpha - 1;
				t[3 * j + 2] = static_cast<uchar>(r + (r - L * 255) * alpha);
				t[3 * j + 1] = static_cast<uchar>(g + (g - L * 255) * alpha);
				t[3 * j] = static_cast<uchar>(b + (b - L * 255) * alpha);
			}
			else
			{
				alpha = Increment;
				t[3 * j + 2] = static_cast<uchar>(L * 255 + (r - L * 255) * (1 + alpha));
				t[3 * j + 1] = static_cast<uchar>(L * 255 + (g - L * 255) * (1 + alpha));
				t[3 * j] = static_cast<uchar>(L * 255 + (b - L * 255) * (1 + alpha));
			}
		}
	}
	imshow("pic", img2);
	return img2;
}

//������
Mat View(Mat img, float weight)
{
	Mat img2, blurred;
	img.copyTo(img2);
	//��˹ģ��
	//��˹�˴�С,X��Y�����ϵĸ�˹�˱�׼ƫ��
	//��� sigmaY Ϊ�㣬��������Ϊ���� sigmaX
	//���������Ϊ�㣬��ֱ����ksize.width ��ksize.height���м��� 
	GaussianBlur(img, blurred, Size(0, 0), 3);
	addWeighted(img, 1 + weight/100, blurred, -weight/100, 0, img2);
	imshow("pic", img2);
	return img2;
}


// �߹����Ӱ(����tip�ж�����һ��)
Mat HighLight_shadow(Mat img, int hs, int tip)
{
	// ���ɻҶ�ͼ
	Mat gray = cv::Mat::zeros(img.size(), CV_32FC1);
	Mat f = img.clone();
	f.convertTo(f, CV_32FC3);
	vector<cv::Mat> pics;
	split(f, pics);//ͨ������
	gray = 0.299f * pics[2] + 0.587 * pics[2] + 0.114 * pics[0];
	gray = gray / 255.f;//��һ��

	// ȷ���߹�������Ӱ��
	Mat thresh = cv::Mat::zeros(gray.size(), gray.type());
	//����������˻�
	if(tip==0)//�߹�
		thresh = gray.mul(gray);
	else if(tip==1)//��Ӱ
		thresh = (1.0f - gray).mul(1.0f - gray);
	// ȡƽ��ֵ��Ϊ��ֵ
	Scalar t = mean(thresh);
	Mat mask = cv::Mat::zeros(gray.size(), CV_8UC1);//Ļ��
	mask.setTo(255, thresh >= t[0]);//��ֵ����mask�д��ڵ���t[0]��ȫ����Ϊ255

	// ��������
	int max = 4;
	float bright = hs / 100.0f / max;
	float mid = 1.0f + max * bright;

	// ��Եƽ������
	Mat midrate = cv::Mat::zeros(img.size(), CV_32FC1);
	Mat brightrate = cv::Mat::zeros(img.size(), CV_32FC1);
	for (int i = 0; i < img.rows; ++i)
	{
		uchar* m = mask.ptr<uchar>(i);
		float* th = thresh.ptr<float>(i);
		float* mi = midrate.ptr<float>(i);
		float* br = brightrate.ptr<float>(i);
		for (int j = 0; j < img.cols; ++j)
		{
			if (m[j] == 255)
			{
				mi[j] = mid;
				br[j] = bright;
			}
			else {
				mi[j] = (mid - 1.0f) / t[0] * th[j] + 1.0f;
				br[j] = (1.0f / t[0] * th[j]) * bright;
			}
		}
	}

	// �߸���midrate��brightrate������������ȡ���ͼ
	Mat result = cv::Mat::zeros(img.size(), img.type());
	for (int i = 0; i < img.rows; ++i)
	{
		float* mi = midrate.ptr<float>(i);
		float* br = brightrate.ptr<float>(i);
		uchar* in = img.ptr<uchar>(i);
		uchar* r = result.ptr<uchar>(i);
		for (int j = 0; j < img.cols; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				float temp = pow(float(in[3 * j + k]) / 255.f, 1.0f / mi[j]) * (1.0 / (1 - br[j]));
				if (temp > 1.0f)
					temp = 1.0f;
				if (temp < 0.0f)
					temp = 0.0f;
				r[3 * j + k] = uchar(255 * temp);
			}
		}
	}
	imshow("pic", result);
	return result;
}

//
Mat Color(Mat img,int color, int tip)
{
	if (img.channels() == 1)
	{
		AfxMessageBox("��ͼ��Ϊ�Ҷ�ͼ");
		return img;
	}
	Mat img2;
	img.copyTo(img2);
	//��ȡͨ��������ֵ
	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			img2.at<Vec3b>(i, j)[tip] = saturate_cast<uchar>(img2.at<Vec3b>(i, j)[tip] + color);
		}
	}
	imshow("pic", img2);
	return img2;
}

