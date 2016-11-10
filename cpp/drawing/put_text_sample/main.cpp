/**
 * OpenCV3 描画サンプル： フォントとテキスト
*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main( int argc, char** argv )
{
    // 表示する文字列
    string text = "Hi Hello World!";

    // 文字の大きさ
    double fontScale = 3;

    // 文字の太さ
    int thickness = 5;

    // フォントの指定
    int fontFace = cv::FONT_HERSHEY_SCRIPT_COMPLEX;

    // 画像マトリックス構造体の作成
    cv::Mat img(600, 800, CV_8UC3, cv::Scalar(200, 150, 100));

    // 文字列表示のベースライン（y座標）
    int baseline = 0;

    // 表示文字列のサイズを取得
    cv::Size textSize = cv::getTextSize(text, fontFace,
                                fontScale, thickness, &baseline);

    // 中央表示位置の計算
    cv::Point textOrg((img.cols - textSize.width)/2,
                  (img.rows + textSize.height)/2);

    // 文字列をBOXで囲む
    baseline += thickness;
    int margin = 10;
    cv::rectangle(img, textOrg + cv::Point(-margin, margin),
              textOrg + cv::Point(textSize.width + margin, -textSize.height - margin),
              cv::Scalar::all(50));

    // 表示ベースラインに下線を引く
    cv::line(img, textOrg + cv::Point(0, thickness),
         textOrg + cv::Point(textSize.width, thickness),
         cv::Scalar(250, 190, 140));

    // 画像マトリックスにテキストを追加
    cv::putText(img, text, textOrg, fontFace, fontScale,
            cv::Scalar::all(250), thickness, 8);

    //　ウィンドウの生成
    string window_name = "TestWindow";
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

    //　ウィンドウに画像マトリックスを表示
    cv::imshow(window_name, img);

    // ユーザが入力するまで待機
    cv::waitKey(0);

    // ウィンドウの破棄（関連するメモリの解放）
    cv::destroyAllWindows();

    // 終了
    return 0;
}
