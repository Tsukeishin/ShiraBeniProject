#ifndef _MANAGER_SCENE_H_INCLUDE_
#define _MANAGER_SCENE_H_INCLUDE_


/* �Q�[����Ԃ̎�� */
enum SCENE
{
	SCENE_TITLE = 0,	// �^�C�g�����
	SCENE_GAME,			// ���C���Q�[��
	SCENE_RESULT,		// ���U���g���
	SCENE_MAX,
	SCENE_END, // �A�v���I��
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
