#ifndef _RESOURCE_TR_H_
#define _RESOURCE_TR_H

#include <QObject>
#include <QDir>
#include <QApplication>

static QString getPath(){
	QDir dir;
	QString path = QCoreApplication::applicationDirPath();
	return path;
}

#define CONFIG_INI "/play.ini"
#define BASICSET_INI "/BasicSet.ini"
#define URL_INI "/url.ini"
#define LANGUAGE_CHINESE "/translation/hsplayer_zh_CN.qm"

#define APP_ICO "/Skin/player/mainicon_ico.ico" 
#define MAIN_LAYOUT "/Skin/player/img.png"

#define PLAYER_CSS "/Skin/player/style.css"

#define BTN_CLOSE_NOR "/Skin/player/window/btn_close_nor.png"
#define BTN_CLOSE_PRESS "/Skin/player/window/btn_close_press.png"
#define BTN_MAXIMIZE_NOR "/Skin/player/window/btn_maximize_nor.png"
#define BTN_MAXIMIZE_PRESS "/Skin/player/window/btn_maximize_press.png"
#define BTN_MINIMIZE_NOR "/Skin/player/window/btn_minimize_nor.png"
#define BTN_MINIMIZE_PRESS "/Skin/player/window/btn_minimize_press.png"

#define BTN_ADD_NOR "/Skin/player/videoList/btn_add_nor.png"
#define BTN_ADD_PRESS "/Skin/player/videoList/btn_add_press.png"
#define BTN_DELT_NOR "/Skin/player/videoList/btn_delt_nor.png"
#define BTN_DELT_PRESS "/Skin/player/videoList/btn_delt_press.png"
#define BTN_MODE_NOR "/Skin/player/videoList/btn_mode_nor.png"
#define BTN_MODE_PRESS "/Skin/player/videoList/btn_mode_press.png"
#define BTN_SEARCH_NOR "/Skin/player/videoList/btn_search_nor.png"
#define BTN_SEARCH_PRESS "/Skin/player/videoList/btn_search_press.png"
#define BTN_SEARCHBOX_NOR "/Skin/player/videoList/btn_searchbox_nor.png"
#define BTN_SEARCHBOX_PRESS "/Skin/player/videoList/btn_searchbox_press.png"
#define BTN_APPEARLIST_NOR "/Skin/player/videoList/btn_appearlist_nor.png"
#define BTN_APPEARLIST_PRESS "/Skin/player/videoList/btn_appearlist_pre.png"
#define IMG_POINT "/Skin/player/videoList/img_point.png"
#define BTN_DATE_NOR "/Skin/player/videoList/btn_date_nor.png"
#define BTN_DATE_PRESS "/Skin/player/videoList/btn_date_press.png"


#define BTN_EXPAND_NOR "/Skin/player/videoSelect/btn_expand_nor.png"
#define BTN_EXPAND_PRESS "/Skin/player/videoSelect/btn_expand_press.png"
#define BTN_FULLSCREEN_NOR "/Skin/player/videoSelect/btn_fullScreen_nor.png"
#define BTN_FULLSCREEN_PRESS "/Skin/player/videoSelect/btn_fullScreen_press.png"
#define BTN_SHOOT_NOR "/Skin/player/videoSelect/btn_shoot_nor.png"
#define BTN_SHOOT_PRESS "/Skin/player/videoSelect/btn_shoot_press.png"
#define BTN_SNAP_NOR "/Skin/player/videoSelect/btn_snap_nor-.png"
#define BTN_SNAP_PRESS "/Skin/player/videoSelect/btn_snap_press.png"

#define BTN_1 "/Skin/player/viewSelect/btn_1.png"
#define BTN_1_PRESS "/Skin/player/viewSelect/btn_1_press.png"
#define BTN_2 "/Skin/player/viewSelect/btn_2.png"
#define BTN_2_PRESS "/Skin/player/viewSelect/btn_2_press.png"
#define BTN_3 "/Skin/player/viewSelect/btn_3.png"
#define BTN_3_PRESS "/Skin/player/viewSelect/btn_3_press.png"
#define BTN_4 "/Skin/player/viewSelect/btn_4.png"
#define BTN_4_PRESS "/Skin/player/viewSelect/btn_4_press.png"

#define BTN_FAST_NOR "/Skin/player/playButton/btn_fast_nor.png"
#define BTN_FAST_PRESS "/Skin/player/playButton/btn_fast_press.png"
#define BTN_HIDELIST_NOR "/Skin/player/playButton/btn_hiddenlist_nor.png"
#define BTN_HIDELIST_PRESS "/Skin/player/playButton/btn_hiddenlist_press.png"
#define BTN_MUTE_NOR "/Skin/player/playButton/btn_mute_nor.png"
#define BTN_MUTE_PRESS "/Skin/player/playButton/btn_mute_press.png"
#define BTN_NEXTFRAME_NOR "/Skin/player/playButton/btn_nextframe_nor.png"
#define BTN_NEXTFRAME_PRESS "/Skin/player/playButton/btn_nextframe_press.png"
#define BTN_OPEN_NOR "/Skin/player/playButton/btn_open_nor.png"
#define BTN_OPEN_PRESS "/Skin/player/playButton/btn_open_press.png"
#define BTN_CHECK_NOR "/Skin/player/playButton/btn_check_nor.png"
#define BTN_CHECK_PRESS "/Skin/player/playButton/btn_check_press.png"
#define BTN_PAUSE_NOR "/Skin/player/playButton/btn_pause_nor.png"
#define BTN_PAUSE_PRESS "/Skin/player/playButton/btn_pause_press.png"
#define BTN_PLAY_NOR "/Skin/player/playButton/btn_play_nor.png"
#define BTN_PLAY_PRESS "/Skin/player/playButton/btn_play_press.png"
#define BTN_SLOW_NOR "/Skin/player/playButton/btn_slow_nor.png"
#define BTN_SLOW_PRESS "/Skin/player/playButton/btn_slow_press.png"
#define BTN_STOP_NOR "/Skin/player/playButton/btn_stop_nor.png"
#define BTN_STOP_PRESS "/Skin/player/playButton/btn_stop_press.png"
#define BTN_VIEW_NOR "/Skin/player/playButton/btn_view_nor.png"
#define BTN_VIEW_PRESS "/Skin/player/playButton/btn_view_press.png"
#define BTN_VOLUME_NOR "/Skin/player/playButton/btn_volume_nor.png"
#define BTN_VOLUME_PRESS "/Skin/player/playButton/btn_volume_press.png"

#define BTN_CANCEL_NOR "/Skin/player/promptBox/btn_cancel_nor.png"
#define BTN_CANCEL_PRESS "/Skin/player/promptBox/btn_cancel_pre.png"
#define BTN_COMFIRM_NOR "/Skin/player/promptBox/btn_confirm_nor.png"
#define BTN_COMFIRM_PRESS "/Skin/player/promptBox/btn_confirm_pre.png"
#define BTN_COMFORMCLOSE_NOR "/Skin/player/promptBox/btn_close_nor.png"

#define BTN_BASICSET_NOR "/Skin/player/set/icon1_nor.png"
#define BTN_BASICSET_PRESS "/Skin/player/set/icon1_press.png"

#define BTN_CAPTURE_NOR "/Skin/player/set/icon2_nor.png"
#define BTN_CAPTURE_PRESS "/Skin/player/set/icon2_press.png"

#define BTN_HOTKEY_NOR "/Skin/player/set/icon3_nor.png"
#define BTN_HOTKEY_PRESS "/Skin/player/set/icon3_press.png"

#define BTN_SETUP_NOR "/Skin/player/disabled/btn_setup_nor.png"
#define BTN_SETUP_PRESS "/Skin/player/disabled/btn_setup_press-.png"
#define BTN_EXPAND_DIS "/Skin/player/disabled/btn_expand_dis.png"
#define BTN_FAST_DIS "/Skin/player/disabled/btn_fast_dis.png"
#define BTN_FULLSCREEN_DIS "/Skin/player/disabled/btn_fullScreen_dis.png"
#define BTN_NEXTFRAME_DIS "/Skin/player/disabled/btn_nextframe_dis.png"
#define BTN_PAUSE_DIS "/Skin/player/disabled/btn_pause_dis.png"
#define BTN_PLAY_DIS "/Skin/player/disabled/btn_play_dis.png"
#define BTN_SHOOT_DIS "/Skin/player/disabled/btn_shoot_dis.png"
#define BTN_SLOW_DIS "/Skin/player/disabled/btn_slow_dis.png"
#define BTN_SNAP_DIS "/Skin/player/disabled/btn_snap_dis.png"

#define BTN_ICON "/Skin/player/disabled/icon.png"

#define BTN_DOWN_NOR "/Skin/player/ScrollBar/btn_down_nor.png"
#define BTN_DOWN_PRESS "/Skin/player/ScrollBar/btn_down_press.png"
#define BTN_TOP_NOR "/Skin/player/ScrollBar/btn_top_nor.png"
#define BTN_TOP_PRESS "/Skin/player/ScrollBar/btn_top_press.png"

#endif