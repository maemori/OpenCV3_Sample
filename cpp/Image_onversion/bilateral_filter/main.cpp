/**
 * OpenCV3．画像変換サンプル： Cannyエッジ検出器.
 *
 * 動画を読み込み、リサイズ＆モノクロ変換を行いエッジ抽出し再生（処理結果を保存）。
 */

/**
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

    // 結果の画像
    cv::Mat dstFrame;

    // バイラテラルフィルタ設定
    int diameter = 10;
    double sigmaColor = 100;
    double sigmaSpace = 50;
    int borderType = cv::BORDER_DEFAULT;

    // 出力ファイル名
    string outputFilename = "output.mp4";

    // ビデオライターの取得
    cv::VideoWriter writer;

    // ビデオライターを開く
    writer.open(
            outputFilename,
            cv::VideoWriter::fourcc('M','J','P','G'),
            capture.get(cv::CAP_PROP_FPS),
            cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH) / 2, capture.get(cv::CAP_PROP_FRAME_HEIGHT) / 2),
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
        // 動画から新しいフレームを取得
        capture >> frame;

        // 再生するフレームがなくなったら終了
        if(frame.empty()) break;

        // 画像を縮小（元の画像の50%）
        cv::Mat resizeFrame(frame.rows / 2, frame.cols / 2, CV_8UC3, cv::Scalar::all(0));
        cv::resize(frame, resizeFrame, resizeFrame.size(), cv::INTER_CUBIC);

        /**
         * 平準化:バイラテラルフィルタ
         *    CvArr* resizeFrame: 入力画像
         *    CvArr* dstFrame: 処理結果画像
         *    int diameter: フィルタリングで利用される各ピクセル近傍領域の直径
         *    double highThresh: 色空間におけるフィルタシグマ
         *    double  apertureSize: S座標空間におけるフィルタシグマ
         *    int borderType
         */
        cv::bilateralFilter(
                resizeFrame,
                dstFrame,
                diameter,
                sigmaColor,
                sigmaSpace,
                borderType
        );

        //　ウィンドウに画像を表示
        cv::imshow(window_name, dstFrame);

        //【出力動画にフレームを追加
        writer << dstFrame;

        // 30ms待機、ユーザが何か入力すると終了
        if(cv::waitKey(30) != -1) break;
    }

    // ウィンドウの破棄（関連するメモリの解放）
    cv::destroyAllWindows();

    // 終了
    return 0;
}
