/**
 * OpenCV3 読込サンプル: 動画を読み込みリサイズ＆モノクロ変換して再生
 * go version go1.7.3
 */
package main

import (
	"os"
	"unsafe"
)

/*
	// OpenCV cooperation.
	// - pkg-config
	#cgo pkg-config: /usr/local/Cellar/opencv3/HEAD-6c12533_4/lib/pkgconfig/opencv.pc
	// - include file
	#include "/usr/local/Cellar/opencv3/HEAD-6c12533_4/include/opencv/highgui.h"
	#include "/usr/local/Cellar/opencv3/HEAD-6c12533_4/include/opencv2/videoio/videoio_c.h"
*/
import "C"

func main() {

	// 動画のファイル
	filename := C.CString("sample_01.mp4")

	//　動画の読み込み
	capture := C.cvCreateFileCapture(filename)
	if(capture == nil) {
		// 終了
		os.Exit(0)
	}

	//【エッジ検出】Cannyエッジ検出器の設定
	lowThresh := 300;
	highThresh := 600;
	apertureSize := 5;

	// 出力ファイル名
	outputFilename := C.CString("output.mp4")

	// 出力動画のFPSの設定
	outputFps := C.cvGetCaptureProperty(capture, C.CV_CAP_PROP_FPS)

	// 出力動画の書き込み画像サイズの取得
	outputSize := C.cvSize(
		(C.int)(C.cvGetCaptureProperty(capture, C.CV_CAP_PROP_FRAME_WIDTH) / 2),
		(C.int)(C.cvGetCaptureProperty(capture, C.CV_CAP_PROP_FRAME_HEIGHT) / 2))

	// 出力動画のコーデックをMPEG-4に指定(mp4)
	var outputFourcc C.int = C.CV_FOURCC('M','J','P','G');

	// 出力動画のカラー設定、カラーは[1]、グレースケールは[0]
	var outputIsColor C.int = 0

	// ビデオライターの取得
	writer := C.cvCreateVideoWriter(outputFilename, outputFourcc, outputFps, outputSize, outputIsColor);

	// 出力動画のフレーム
	output := C.cvCreateImage(outputSize, C.IPL_DEPTH_8U, C.CV_8UC3)

	// ビデオライターの初期化を確認
	if (writer == nil) {
		os.Exit(0)
	}

	// 動画から取得するフレーム
	var frame *C.IplImage

	// リサイズ用フレーム
	var resizeFrame *C.CvMat
	resizeFrame = C.cvCreateMat(outputSize.height, outputSize.width, C.CV_8UC3)

	// グレースケール用フレーム（モノクロ用のシングルチャンネル）
	var gray *C.CvMat
	gray = C.cvCreateMat(outputSize.height, outputSize.width, C.CV_8UC1)

	// エッジ用フレーム（モノクロ用のシングルチャンネル）
	var edges *C.CvMat
	edges = C.cvCreateMat(outputSize.height, outputSize.width, C.CV_8UC1)

	//　ウィンドウの生成
	window_name := C.CString("TestWindow")
	C.cvNamedWindow(window_name, C.CV_WINDOW_AUTOSIZE)

	// 動画の再生
	for {
		// 動画から新しいフレームを取得
		frame = C.cvQueryFrame(capture);

		// 再生するフレームがなくなったら終了
		if(frame == nil) {
			break
		}

		// 画像を縮小（元の画像の50%）
		C.cvResize(unsafe.Pointer(frame), unsafe.Pointer(resizeFrame), C.CV_INTER_CUBIC)

		// フレームをグレースケールに変換
		C.cvCvtColor(unsafe.Pointer(resizeFrame), unsafe.Pointer(gray), C.CV_BGR2GRAY)

		/**
		 * 【エッジ検出】Cannyエッジ検出器の実行
		 *    CvArr* gray: 入力画像（グレースケール）
		 *    CvArr* edges: 処理結果画像（グレースケール）
		 *    double lowThresh: ヒステリシス閾値の下限
		 *    double highThresh: ヒステリシス閾値の上限
		 *    int  apertureSize: Sobel微分オペレータが使用するアパーチャ
		 */
		C.cvCanny(
			unsafe.Pointer(gray),
			unsafe.Pointer(edges),
			(C.double)(lowThresh),
			(C.double)(highThresh),
			(C.int)(apertureSize))

		//　ウィンドウに画像を表示
		C.cvShowImage(window_name, unsafe.Pointer(edges))

		// Mat構造体をIplImage構造体に変換
		output = C.cvGetImage(unsafe.Pointer(edges), unsafe.Pointer(output))

		//【動画の出力】動画にフレームを追加
		C.cvWriteFrame(writer, unsafe.Pointer(output))

		// 30ms待機、ユーザが何か入力すると終了
		if(C.cvWaitKey(30) != -1) {
			break
		}
	}

	// ビデオキャプチャーの解放
	C.cvReleaseCapture (&capture)

	// ビデオライターの解放
	C.cvReleaseVideoWriter(&writer)

	// ウィンドウの破棄（関連するメモリの解放）
	C.cvDestroyAllWindows()

	// 終了
	os.Exit(0)

}
