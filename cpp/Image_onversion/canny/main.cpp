/**
 * OpenCV3．画像変換サンプル： Cannyエッジ検出器サンプル
 *
 *
 * 1986年にJ.Cannyに寄って洗練されたエッジ検出器。
 *
 * 個々のエッジの候補値ピクセルから輪郭を作り上げようとします。
 * この輪郭はヒステリシス閾値をピクセルに適用することで形成されます。
 * ヒステリスス閾値は上限と下限を指定し、ピクセルが上限の閾値より大きい勾配を持っているっ場合はエッジのピクセルとして受け入れられます。
 * 下限の閾値より小さいと破棄され、間の場合は高い閾値も上のピクセルと繋がっている場合だけ受け入れられます。
 * 上限と下限の推奨比率は2:1、3:1の間です。
 * また、正方形フィルタの幅であるアパーチャの値を指定します。アパーチャの値は1、3、5、7がサポートされています。
 *
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

    // 1チャンネル用画像
    cv::Mat gray;

    // Cannyエッジ検出器の設定
    double lowThresh = 300;
    double highThresh = 600;
    int  apertureSize = 5;

    // エッジ検出結果の画像
    cv::Mat edges;

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

        /**
         * Cannyエッジ検出器の実行
         *    CvArr* gray: 入力画像（グレースケール）
         *    CvArr* edges: 処理結果画像（グレースケール）
         *    double lowThresh: ヒステリシス閾値の下限
         *    double highThresh: ヒステリシス閾値の上限
         *    int  apertureSize: Sobel微分オペレータが使用するアパーチャ
         */
        cv::Canny(gray, edges, lowThresh, highThresh, apertureSize);

        //　ウィンドウに画像を表示
        cv::imshow(window_name, edges);

        // 30ms待機、ユーザが何か入力すると終了
        if(cv::waitKey(30) != -1) break;
    }

    // ウィンドウの破棄（関連するメモリの解放）
    cv::destroyAllWindows();

    // 終了
    return 0;
}
