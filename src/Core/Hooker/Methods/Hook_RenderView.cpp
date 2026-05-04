#include "Hook_RenderView.hpp"

auto Hook_RenderView(
    void* pViewRender,
    CViewSetup* view,
    const int flags,
    const int toDraw
) -> void {

    // view->fovViewmodel = 120;
	static auto camPos = Vector3 { 0,0,0 };

    float speed = 2.0;
    // if ( camPos.Zero() )
    //     camPos = view->origin;

    // if (Globals::lastCmd.buttonFlags & static_cast<int>(CUserCmd::ButtonFlag::Speed))
    //     speed *= 5.f;
    // if (Globals::lastCmd.buttonFlags & static_cast<int>(CUserCmd::ButtonFlag::Duck))
    //     speed *= 0.5f;
    // if (Globals::lastCmd.buttonFlags & static_cast<int>(CUserCmd::ButtonFlag::Jump))
    //     camPos.z += speed;
    //
    // if (Globals::lastCmd.buttonFlags & static_cast<int>(CUserCmd::ButtonFlag::Forward))
    //     camPos += (view.angles.toVector() * speed);
    //
    // if (Globals::lastCmd.buttonFlags & static_cast<int>(CUserCmd::ButtonFlag::Back))
    //     camPos -= (view.angles.toVector() * speed);
    //
    // if (Globals::lastCmd.buttonFlags & static_cast<int>(CUserCmd::ButtonFlag::MoveLeft))
    //     camPos += (view.angles.SideVector() * speed);
    //
    // if (Globals::lastCmd.buttonFlags & static_cast<int>(CUserCmd::ButtonFlag::MoveRight))
    //     camPos -= (view.angles.SideVector() * speed);

    // view->origin = camPos;
    return RenderView_o(pViewRender, view, flags, toDraw);
}
