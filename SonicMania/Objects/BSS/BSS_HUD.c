// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: BSS_HUD Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectBSS_HUD *BSS_HUD;

void BSS_HUD_Update(void) {}

void BSS_HUD_LateUpdate(void) {}

void BSS_HUD_StaticUpdate(void) {}

void BSS_HUD_Draw(void)
{
    RSDK_THIS(BSS_HUD);

    Vector2 drawPos;
    drawPos.x = (ScreenInfo->center.x - 141) << 16;
    drawPos.y = 0xD0000;
    RSDK.DrawSprite(&self->sphereAnimator, &drawPos, true);

    drawPos.x += 0x250000;
    drawPos.y = 0x110000;
    BSS_HUD_DrawNumbers(BSS_Setup->sphereCount, &drawPos);

    drawPos.x = (ScreenInfo->center.x + 64) << 16;
    drawPos.y = 0xD0000;
    RSDK.DrawSprite(&self->ringAnimator, &drawPos, true);

    drawPos.x += 0x380000;
    drawPos.y = 0x110000;
    BSS_HUD_DrawNumbers(BSS_Setup->ringCount, &drawPos);
}

void BSS_HUD_Create(void *data)
{
    RSDK_THIS(BSS_HUD);

    if (!SceneInfo->inEditor) {
        self->active        = ACTIVE_NORMAL;
        self->visible       = true;
        self->drawGroup     = DRAWGROUP_COUNT - 1;
        self->updateRange.x = 0x800000;
        self->updateRange.y = 0x800000;

        RSDK.SetSpriteAnimation(BSS_HUD->aniFrames, 0, &self->sphereAnimator, true, 0);
        RSDK.SetSpriteAnimation(BSS_HUD->aniFrames, 0, &self->ringAnimator, true, 1);
        RSDK.SetSpriteAnimation(BSS_HUD->aniFrames, 1, &self->numbersAnimator, true, 0);
    }
}

void BSS_HUD_StageLoad(void)
{
    BSS_HUD->aniFrames = RSDK.LoadSpriteAnimation("SpecialBS/HUD.bin", SCOPE_STAGE);

    RSDK.ResetEntitySlot(SLOT_BSS_HUD, BSS_HUD->classID, NULL);
}

void BSS_HUD_DrawNumbers(int32 value, Vector2 *drawPos)
{
    RSDK_THIS(BSS_HUD);

    int32 mult = 1;
    for (int32 i = 0; i < 3; ++i) {
        self->numbersAnimator.frameID = value / mult % 10;
        RSDK.DrawSprite(&self->numbersAnimator, drawPos, true);
        drawPos->x -= 0x100000;
        mult *= 10;
    }
}

#if RETRO_INCLUDE_EDITOR
void BSS_HUD_EditorDraw(void) {}

void BSS_HUD_EditorLoad(void) {}
#endif

void BSS_HUD_Serialize(void) {}
