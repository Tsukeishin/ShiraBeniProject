#ifndef _MANAGER_SCENE_H_INCLUDE_
#define _MANAGER_SCENE_H_INCLUDE_


/* ゲーム状態の種類 */
enum SCENE
{
	SCENE_TITLE = 0,	// タイトル画面
	SCENE_GAME,			// メインゲーム
	SCENE_RESULT,		// リザルト画面
	SCENE_MAX,
	SCENE_END, // アプリ終了
};


typedef class SceneManager
{
	static SCENE GameScene;

public:
	static int  Update();
	static void Draw();
	static SCENE SetScene(SCENE scene);

}Scene;


#endif // !_MANAGER_SCENE_H_INCLUDE_
