/**
 * OpenCV3．画像変換サンプル： Hough線変換
 *
 * プログレッシブな確率的Hough変換(PPHT:Progressive Probabilistic Hough Transform)を用いて動画から直線の抽出を行います。
 *
 * 処理順序:
 * 1. 動画のフレームの読み込み
 * 2. 画像を縮小(resize)
 * 3. グレースケールに変換(cvtColor)
 * 4. 平準化の実行:バイラテラルフィルタ(bilateralFilter)
 * 5. エッジ検出器の実行:Canny(Canny)
 * 6. Hough線変換:プログレッシブな確率的Hough変換(HoughLinesP)
 * 7. 処理結果のフレームを再生し保存
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main( int argc, char** argv )
{
    /**
     * 設定.
     */

    // 入力動画ファイル
    string inputFilename = "sample_01.mp4";

    // 出力動画ファイル名
    string outputFilename = "output.mp4";

    // 画像処理用リサイズの値(50%)
    const double RESIZE_SCALE = 0.5;

    // Cannyエッジ検出器
    const double LOW_THRESH = 300;
    const double HIGH_THRESH = 600;
    const int  APERTURE_SIZE = 5;

    // バイラテラルフィルタ設定
    const int DIAMETER = 10;
    const double SIGMA_COLOR = 100;
    const double SIGMA_SPACE = 50;
    const int BORDER_TYPE = cv::BORDER_DEFAULT;

    // Hough線変換設定
    const double RHO = 1;
    const double THETA = CV_PI / 180;
    const int THRESHOLD = 100;
    const double MIN_LINE_LENGTH = 70;
    const double MAX_LINE_GAP = 10;

    /**
     * 処理.
     */

    //　動画の読み込み
    cv::VideoCapture capture(inputFilename);
    if(!capture.isOpened())
        return -1;

    // 入力動画から取得するフレーム
    cv::Mat inputFrame;

    // 1チャンネル用のフレーム
    cv::Mat grayFrame;

    // オリジナルサイズ
    cv::Size originalSize = cv::Size((int)(capture.get(cv::CAP_PROP_FRAME_WIDTH)), (int)(capture.get(cv::CAP_PROP_FRAME_HEIGHT)));

    // 縮小サイズ
    cv::Size resizeSize = cv::Size((int)(originalSize.width * RESIZE_SCALE), (int)(originalSize.height * RESIZE_SCALE));

    // 縮小用のフレーム
    cv::Mat resizeFrame(resizeSize, CV_8UC3, cv::Scalar::all(0));

    // 平準化結果の画像フレーム
    cv::Mat filterFrame;

    // エッジ検出結果のフレーム
    cv::Mat edgesFrame;

    // 処理結果用のフレーム
    cv::Mat dstFrame;

    // ビデオライターの取得
    cv::VideoWriter writer;

    // 1フレームの処理の開始と終了時間
    time_t startTime, endTime;

    // 1フレームあたりのディレィ
    const double delay = 1000 / capture.get(cv::CAP_PROP_FPS);

    // ビデオライターを開く
    writer.open(
            outputFilename,
            cv::VideoWriter::fourcc('M','J','P','G'),
            capture.get(cv::CAP_PROP_FPS),
            resizeSize,
            true
    );

    // ビデオライターの初期化を確認
    if (!writer.isOpened())
        return -1;

    //　ウィンドウの生成
    string window_name = "Test Window";
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

    // 動画の再生
    while(true) {
        // Start time
        time(&startTime);

        // 動画から新しいフレームを取得
        capture >> inputFrame;

        // 再生するフレームがなくなったら終了
        if(inputFrame.empty()) break;

        // 画像を縮小
        cv::resize(inputFrame, resizeFrame, resizeSize, cv::INTER_CUBIC);

        // フレームをグレースケールに変換
        cv::cvtColor(resizeFrame, grayFrame, cv::COLOR_BGR2GRAY);

        // 平準化の実行:バイラテラルフィルタ
        cv::bilateralFilter(resizeFrame, filterFrame, DIAMETER, SIGMA_COLOR, SIGMA_SPACE, BORDER_TYPE);

        // エッジ検出器の実行:Canny
        cv::Canny(filterFrame, edgesFrame, LOW_THRESH, HIGH_THRESH, APERTURE_SIZE);

        // 出力用のフレームを設定
        dstFrame = resizeFrame;

        // 線抽出結果格納用
        vector<cv::Vec4i> lines;

        /**
         * Hough線変換:プログレッシブな確率的Hough変換(PPHT:Progressive Probabilistic Hough Transform)
         *    CvArr* resizeFrame: 入力画像
         *    vector<cv::Vec4i> lines: 抽出された線の結果が格納されるポインタ
         *    double RHO: アキュームレイター平面分解能のピクセル単位
         *    double THETA: アキュームレイター平面分解能のラジアン単位
         *    int THRESHOLD: 線判断閾値
         *    double MIN_LINE_LENGTH: 線分の最小値
         *    double MAX_LINE_GAP: 線結合の線分間の距離
         */
        HoughLinesP(
                edgesFrame,
                lines,
                RHO,
                THETA,
                THRESHOLD,
                MIN_LINE_LENGTH,
                MAX_LINE_GAP);

        // 抽出された線を画像に追加
        for( size_t i = 0; i < lines.size(); i++ )
        {
            cv::Vec4i l = lines[i];
            cv::line( dstFrame, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar::all(255), 3, CV_AA);
        }

        //　ウィンドウに画像を表示
        cv::imshow(window_name, dstFrame);

        //【出力動画にフレームを追加
        writer << dstFrame;

        // End Time
        time(&endTime);

        // 1フレーム処理時間
        double seconds = difftime (endTime, startTime);

        // FPSを基準とした時間から処理時間を引いた時間で待機、ユーザが何か入力すると終了
        int waitTime = (int)(delay - seconds);
        if(cv::waitKey(waitTime) >= 0) break;
    }

    // ウィンドウの破棄（関連するメモリの解放）
    cv::destroyAllWindows();

    // 終了
    return 0;
}
