/**
 * OpenCV3 描画サンプル： 動画を読み込みリサイズ＆モノクロ変換して再生
*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main( int argc, char** argv )
{
    // 動画のファイル
    string filename = "sample_01.mp4";

    //　動画の読み込み
    cv::VideoCapture capture(filename);
    if(!capture.isOpened())
        return -1;

    // 動画から取得するフレーム
    cv::Mat frame;

    // 表示用フレーム
    cv::Mat gray;

    //　ウィンドウの生成
    string window_name = "Test Window";
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

    // 動画の再生
    while(true) {
        // 動画から新しいフレームを取得
        capture >> frame;

        // 再生するフレームがなくなったら終了
        if(frame.empty()) break;

        // 画像を縮小（元の画像の50%）
        cv::Mat resizeFrame(frame.rows / 2, frame.cols / 2, CV_8UC3, cv::Scalar::all(0));
        cv::resize(frame, resizeFrame, resizeFrame.size(), cv::INTER_CUBIC);

        // フレームをグレースケールに変換
        cv::cvtColor(resizeFrame, gray, cv::COLOR_BGR2GRAY);

        //　ウィンドウに画像を表示
        cv::imshow(window_name, gray);

        // 30ms待機、ユーザが何か入力すると終了
        if(cv::waitKey(30) != -1) break;
    }

    // ウィンドウの破棄（関連するメモリの解放）
    cv::destroyAllWindows();

    // 終了
    return 0;
}
