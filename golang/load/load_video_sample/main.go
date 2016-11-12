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

	// 動画から取得するフレーム
	var frame *C.IplImage

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
		resizeFrame := C.cvCreateMat(frame.height / 2, frame.width / 2, C.CV_8UC3)
		C.cvResize(unsafe.Pointer(frame), unsafe.Pointer(resizeFrame), C.CV_INTER_CUBIC)

		// 表示用フレーム（モノクロ用のシングルチャンネル）
		size := C.cvGetSize(unsafe.Pointer(resizeFrame))
		gray := C.cvCreateMat(size.height, size.width, C.CV_8UC1)

		// フレームをグレースケールに変換
		C.cvCvtColor(unsafe.Pointer(resizeFrame), unsafe.Pointer(gray), C.CV_BGR2GRAY)

		//　ウィンドウに画像を表示
		C.cvShowImage(window_name, unsafe.Pointer(gray))

		// 30ms待機、ユーザが何か入力すると終了
		if(C.cvWaitKey(30) != -1) {
			break
		}
	}

	// ウィンドウの破棄（関連するメモリの解放）
	C.cvDestroyAllWindows()

	// 終了
	os.Exit(0)

}
