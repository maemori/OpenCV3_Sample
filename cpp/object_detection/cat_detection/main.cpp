/**
 * OpenCV3．物体認識サンプル： リアルタイム猫顔認識
 *
 * カメラから入力されたライブ動画から顔を識別し置換用の画像で置き換えます。処理結果はリアルタイムに表示し動画ファイルとしても保存を行います。
 *
 * 処理順序:
 * 1. 動画のフレームの読み込み
 * 2. 画像を縮小(resize)
 * 3. グレースケールに変換(cvtColor)
 * 4. 物体検出(detectMultiScale)
 * 5. 検出された物体を加工
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/face.hpp>

using namespace std;

/**
 * 画像を重ねる。
 *
 * @param basicImage 重ねる基礎となる画像
 * @param overlapImage 重ねる画像
 * @param compositionStart 前景画像の左上座標
 * @param compositionEnd 前景画像の右下座標
 * @return
 */
cv::Mat imagePileUp(
        const cv::Mat &basicImage,
        const cv::Mat &overlapImage,
        const cv::Point2f compositionStart,
        const cv::Point2f compositionEnd)
{
    //背景画像の作成
    cv::Mat dstImage;
    basicImage.copyTo(dstImage);

    //３組の対応点を作成
    vector<cv::Point2f> src, dst;
    src.push_back(cv::Point2f(0, 0));
    src.push_back(cv::Point2f(overlapImage.cols, 0));
    src.push_back(cv::Point2f(overlapImage.cols, overlapImage.rows));
    dst.push_back(compositionStart);
    dst.push_back(cv::Point2f(compositionEnd.x, compositionStart.y));
    dst.push_back(compositionEnd);

    // 前景画像の変形行列
    cv::Mat mat = cv::getAffineTransform(src, dst);

    // アフィン変換の実行
    cv::warpAffine(overlapImage, dstImage, mat, dstImage.size(), CV_INTER_LINEAR, cv::BORDER_TRANSPARENT);

    return dstImage;
}

/**
 * メイン処理.
 *
 * @param argc
 * @param argv
 * @return
 */
int main( int argc, char** argv )
{
    /**
     * 設定.
     */

    // 分類器の指定
    std::string cascadeName;
    cascadeName = "./resource/cascade/haarcascade_frontalcatface_extended.xml";

    // 出力動画ファイル名
    string outputFilename = "output.mp4";

    // 画像のファイル
    string pileUpFilename = "./resource/logo.jpeg";

    // 画像処理用リサイズの値(20%)
    const double RESIZE_SCALE = 0.2;

    /**
     * 処理.
     */

    //　動画の読み込み
    cv::VideoCapture capture(0);
    if(!capture.isOpened())
        return -1;

    // 分類器の読み込み
    cv::CascadeClassifier cascade;
    if(!cascade.load(cascadeName))
        return -1;

    // 置換用の画像を読み込み
    cv::Mat pileUpImage = cv::imread(pileUpFilename, cv::IMREAD_COLOR);

    // 置換用の画像のリサイズ結果を格納
    cv::Mat resizePileUpImage;

    // 入力動画から取得するフレーム
    cv::Mat inputFrame;

    // 1チャンネル用のフレーム
    cv::Mat grayFrame;

    // オリジナルサイズ
    cv::Size originalSize ((int)(capture.get(cv::CAP_PROP_FRAME_WIDTH)), (int)(capture.get(cv::CAP_PROP_FRAME_HEIGHT)));

    // 縮小サイズ
    cv::Size resizeSize ((int)(originalSize.width * RESIZE_SCALE), (int)(originalSize.height * RESIZE_SCALE));

    // 縮小用のフレーム
    cv::Mat resizeFrame(resizeSize, CV_8UC3, cv::Scalar::all(0));

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
            originalSize,
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

        // 出力用のフレームを設定
        dstFrame = inputFrame;

        /**
         * 入力画像中から異なるサイズの物体を検出します．検出された物体は，矩形のリストとして返されます．
         *
         * cv::Mat grayFrame - CV_8U 型の行列．ここに格納されている画像中から物体が検出されます
         * std::vector<cv::Rect> objects - 矩形を要素とするベクトル それぞれの矩形は、検出した物体を含みます
         * double scaleFactor - 各画像スケールにおける縮小量
         * int minNeighbors - 物体候補となる矩形は，最低でもこの数だけの近傍矩形を含む必要がある
         * int flags - このパラメータは，新しいカスケードでは未使用
         * cv::Size minSize - 物体が取り得る最小サイズ．これよりも小さい物体を無視
         */
        // 物体検出結果格納用
        std::vector<cv::Rect> objects;
        // 物体検出の設定
        double scaleFactor = 1.1;
        int minNeighbors = 3;
        int flags = 0;
        cv::Size minSize(30, 30);
        // 物体検出の実行
        cascade.detectMultiScale(grayFrame, objects,
                                 scaleFactor,
                                 minNeighbors,
                                 flags,
                                 cv::Size(30, 30));

        // 検出結果を処理
        std::vector<cv::Rect>::const_iterator object = objects.begin();
        for(; object != objects.end(); ++object) {
            // 置き換え用の画像を検出結果の大きさに変更
            int xSize = (int)(object->x / RESIZE_SCALE + object->width / RESIZE_SCALE);
            int ySize = (int)(object->y / RESIZE_SCALE + object->height/ RESIZE_SCALE);
            cv::Size pileUpImageSize = cv::Size(xSize, ySize);
            cv::resize(pileUpImage, resizePileUpImage, pileUpImageSize, cv::INTER_CUBIC);

            // 合成画像座標を指定
            cv::Point2f compositionStart(int(object->x / RESIZE_SCALE), int(object->y / RESIZE_SCALE));
            cv::Point2f compositionEnd(
                    int(object->x / RESIZE_SCALE + object->width / RESIZE_SCALE),
                    int(object->y / RESIZE_SCALE + object->height/ RESIZE_SCALE));

            // 検出されたオブジェクトを合成画像で置換
            dstFrame = imagePileUp(dstFrame, pileUpImage, compositionStart, compositionEnd);

            // 検出されたオブジェクトを四角で囲む
            cv::rectangle(
                    dstFrame,
                    cv::Point(compositionStart),
                    cv::Point(compositionEnd),
                    cv::Scalar(50,50,150),
                    3,
                    CV_AA);
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
