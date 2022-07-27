#include <time.h>
#include <algorithm>
#include "game_main.h"
#include "../dxlib_ext/dxlib_ext.h"

dxe::Camera* camera = nullptr;
dxe::Mesh* mesh = nullptr;
float speed_ = 2;
bool init = false;

void gameMain(float delta_time) {
	if (!init) {
		camera = new dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
		camera->pos_ = { 100, 100, -300 };
		mesh = dxe::Mesh::CreateBoxMV(50);
		mesh->setTexture("graphics/box.bmp");
		mesh->flg_dbg_line_ = dxe::Mesh::fDebugLine::FLG_AXIS;

		init = true;
	}

	//オブジェクト回転
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) {
		//面倒な書き方
		/*tnl::Matrix tm = tnl::Matrix::Translation({ 0, 1, 0 });
		tnl::Matrix rm = mesh->rot_q_.getMatrix();
		tnl::Matrix wm = tm * rm;
		tnl::Vector3 axis = { wm._41, wm._42, wm._43 };*/
		
		//比較的簡単な書き方
		tnl::Vector3 axis = tnl::Vector3::TransformCoord({ 0, -1, 0 }, mesh->rot_q_);

		mesh->rot_q_ *= tnl::Quaternion::RotationAxis(axis, tnl::ToRadian(1));

	}
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) {
		/*tnl::Matrix tm = tnl::Matrix::Translation({ 0, 1, 0 });
		tnl::Matrix rm = mesh->rot_q_.getMatrix();
		tnl::Matrix wm = tm * rm;
		tnl::Vector3 axis = { wm._41, wm._42, wm._43 };*/

		tnl::Vector3 axis = tnl::Vector3::TransformCoord({ 0, 1, 0 }, mesh->rot_q_);

		mesh->rot_q_ *= tnl::Quaternion::RotationAxis(axis, tnl::ToRadian(1));

	}
	if (tnl::Input::IsKeyDown(eKeys::KB_UP)) {
		/*tnl::Matrix tm = tnl::Matrix::Translation({1, 0, 0});
		tnl::Matrix rm = mesh->rot_q_.getMatrix();
		tnl::Matrix wm = tm * rm;
		tnl::Vector3 axis = { wm._41, wm._42, wm._43 };*/

		tnl::Vector3 axis = tnl::Vector3::TransformCoord({ 1, 0, 0 }, mesh->rot_q_);

		mesh->rot_q_ *= tnl::Quaternion::RotationAxis(axis, tnl::ToRadian(1));
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_DOWN)) {
		/*tnl::Matrix tm = tnl::Matrix::Translation({1, 0, 0});
		tnl::Matrix rm = mesh->rot_q_.getMatrix();
		tnl::Matrix wm = tm * rm;
		tnl::Vector3 axis = { wm._41, wm._42, wm._43 };*/

		tnl::Vector3 axis = tnl::Vector3::TransformCoord({ -1, 0, 0 }, mesh->rot_q_);

		mesh->rot_q_ *= tnl::Quaternion::RotationAxis(axis, tnl::ToRadian(1));
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_Z)) {
		/*tnl::Matrix tm = tnl::Matrix::Translation({0, 0, 1});
		tnl::Matrix rm = mesh->rot_q_.getMatrix();
		tnl::Matrix wm = tm * rm;
		tnl::Vector3 axis = { wm._41, wm._42, wm._43 };*/

		tnl::Vector3 axis = tnl::Vector3::TransformCoord({ 0, 0, 1 }, mesh->rot_q_);

		mesh->rot_q_ *= tnl::Quaternion::RotationAxis({ 0, 0, 1 }, tnl::ToRadian(1));
	}

	//オブジェクト移動
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		mesh->pos_ += tnl::Vector3::TransformCoord({ 0, 0, 1 }, mesh->rot_q_) * speed_;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		mesh->pos_ += tnl::Vector3::TransformCoord({ -1, 0, 0 }, mesh->rot_q_) * speed_;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		mesh->pos_ += tnl::Vector3::TransformCoord({ 0, 0, -1 }, mesh->rot_q_) * speed_;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		mesh->pos_ += tnl::Vector3::TransformCoord({ 1, 0, 0 }, mesh->rot_q_) * speed_;
	}

	camera->update();

	mesh->render(camera);

	DrawGridGround(50, 20);
}

