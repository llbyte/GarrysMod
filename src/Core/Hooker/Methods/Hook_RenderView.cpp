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

    // if (Globals::lastCmd.buttons & IN_SPEED)
    //     speed *= 5.f;
    // if (Globals::lastCmd.buttons & IN_DUCK)
    //     speed *= 0.5f;
    // if (Globals::lastCmd.buttons & IN_JUMP)
    //     camPos.z += speed;
    //
    // if (Globals::lastCmd.buttons & IN_FORWARD)
    //     camPos += (view.angles.toVector() * speed);
    //
    // if (Globals::lastCmd.buttons & IN_BACK)
    //     camPos -= (view.angles.toVector() * speed);
    //
    // if (Globals::lastCmd.buttons & IN_MOVELEFT)
    //     camPos += (view.angles.SideVector() * speed);
    //
    // if (Globals::lastCmd.buttons & IN_MOVERIGHT)
    //     camPos -= (view.angles.SideVector() * speed);

    // view->origin = camPos;
    return RenderView_o(pViewRender, view, flags, toDraw);
}
