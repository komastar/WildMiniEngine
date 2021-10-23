#pragma once
#define SAFE_DELETE(p)              if (p) { delete (p); } (p) = NULL;
#define SAFE_DELETE_ARRAY(p)        if (p) { delete[] (p); } (p) = NULL;

#define SAFE_START(p)               if (p) { (p)->Start(); }
#define SAFE_UPDATE(p)              if (p) { (p)->Update(); }
#define SAFE_RENDER(p)              if (p) { (p)->Render(); }
#define SAFE_RELEASE(p)             if (p) { (p)->Release(); (p) = NULL; }
