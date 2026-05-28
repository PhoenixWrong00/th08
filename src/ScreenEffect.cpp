#include "ScreenEffect.hpp"

namespace th08
{

DIFFABLE_STATIC(i32, g_ScreenEffectCounter);
DIFFABLE_STATIC(ScreenEffect, g_ScreenEffect);

void ScreenEffect::Clear(D3DCOLOR color)
{
    g_Supervisor.d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0, 0);
    if (g_Supervisor.d3dDevice->Present(NULL, NULL, NULL, NULL) < 0)
    {
        g_Supervisor.d3dDevice->Reset(&g_Supervisor.presentParameters);
    }
    g_Supervisor.d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0, 0);
    if (g_Supervisor.d3dDevice->Present(NULL, NULL, NULL, NULL) < 0)
    {
        g_Supervisor.d3dDevice->Reset(&g_Supervisor.presentParameters);
    }
    return;
}

void ScreenEffect::SetViewport(D3DCOLOR clearColor)
{
    if(g_AnmManager != 0){
      g_AnmManager->FlushVertexBuffer();
    }
    g_Supervisor.viewport.X = 0;
    g_Supervisor.viewport.Y = 0;
    g_Supervisor.viewport.Width = GAME_WINDOW_WIDTH;
    g_Supervisor.viewport.Height = GAME_WINDOW_HEIGHT;
    g_Supervisor.viewport.MinZ = 0.0;
    g_Supervisor.viewport.MaxZ = 1.0;
    g_Supervisor.d3dDevice->SetViewport(&g_Supervisor.viewport);
    Clear(clearColor);
}

ChainCallbackResult ScreenEffect::CalcFadeIn(ScreenEffect *screenEffect)
{
    if (screenEffect->effectLength != 0)
    {
        screenEffect->fadeAlpha = 255.0f - (((float)screenEffect->timer * 255.0f) / screenEffect->effectLength);
        if ((i32)screenEffect->fadeAlpha < 0)
        {
            screenEffect->fadeAlpha = 0;
        }
    }

    if (screenEffect->timer >= screenEffect->effectLength)
    {
        return CHAIN_CALLBACK_RESULT_CONTINUE_AND_REMOVE_JOB;
    }

    screenEffect->timer++;
    return CHAIN_CALLBACK_RESULT_CONTINUE;
}

void ScreenEffect::DrawSquare(ZunRect *rectDimensions, D3DCOLOR color)
{
    g_AnmManager->FlushVertexBuffer();

    VertexDiffuseXyzrhw vertices[4];

    memcpy(&vertices[0].pos, &Float3(rectDimensions->left, rectDimensions->top, 0.0f), sizeof(Float3));
    memcpy(&vertices[1].pos, &Float3(rectDimensions->right, rectDimensions->top, 0.0f), sizeof(Float3));
    memcpy(&vertices[2].pos, &Float3(rectDimensions->left, rectDimensions->bottom, 0.0f), sizeof(Float3));
    memcpy(&vertices[3].pos, &Float3(rectDimensions->right, rectDimensions->bottom, 0.0f), sizeof(Float3));
    vertices[0].w = vertices[1].w = vertices[2].w = vertices[3].w = 1.00f;
    vertices[0].diffuse = vertices[1].diffuse = vertices[2].diffuse = vertices[3].diffuse = color;

    g_Supervisor.d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
    g_Supervisor.d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    g_Supervisor.d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
    g_Supervisor.d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
    if (!g_Supervisor.IsDepthTestDisabled())
    {
        g_Supervisor.d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
    }

    g_Supervisor.d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    g_Supervisor.d3dDevice->SetVertexShader(D3DFVF_DIFFUSE | D3DFVF_XYZRHW);
    g_Supervisor.d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(*vertices));
    g_AnmManager->ClearVertexShader();
    g_AnmManager->ClearSprite();
    g_AnmManager->ClearTexture();
    g_AnmManager->ClearColorOp();
    g_AnmManager->ClearBlendMode();
    g_AnmManager->ClearZWrite();

    g_Supervisor.d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    g_Supervisor.d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    g_Supervisor.d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    g_Supervisor.d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}

// STUB: th08 0x45b490
void ScreenEffect::DrawSquareShaded(ZunRect *rect, D3DCOLOR topLeft, D3DCOLOR topRight, D3DCOLOR bottomLeft,
                                    D3DCOLOR bottomRight)
{
}

// STUB: th08 0x45b760
ChainCallbackResult ScreenEffect::CalcFadeOut(ScreenEffect *screenEffect)
{
    return CHAIN_CALLBACK_RESULT_CONTINUE;
}

// STUB: th08 0x45b8b0
ScreenEffect *ScreenEffect::RegisterChain(ScreenEffectType effect, i32 ticks, i32 param_3, i32 param_4, i32 param_5,
                                          i32 param_6)
{
    return NULL;
}

// STUB: th08 0x45bb50
ChainCallbackResult ScreenEffect::DrawFullFade(ScreenEffect *screenEffect)
{
    return CHAIN_CALLBACK_RESULT_CONTINUE;
}

// STUB: th08 0x45bc40
ChainCallbackResult ScreenEffect::DrawArcadeFade(ScreenEffect *screenEffect)
{
    return CHAIN_CALLBACK_RESULT_CONTINUE;
}

// STUB: th08 0x45bdc0
ChainCallbackResult ScreenEffect::CalcShake(ScreenEffect *screenEffect)
{
    return CHAIN_CALLBACK_RESULT_CONTINUE;
}

// STUB: th08 0x45c0e0
ZunResult ScreenEffect::AddedCallback(ScreenEffect *screenEffect)
{
    return ZUN_SUCCESS;
}

// STUB: th08 0x45c100
ZunResult ScreenEffect::DeletedCallback(ScreenEffect *screenEffect)
{
    return ZUN_SUCCESS;
}

} /* namespace th08 */
