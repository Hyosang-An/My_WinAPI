// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"
#include "Resource.h"

// STL 
#include <vector>
#include <list>
#include <map>
#include <string>

#include <assert.h>
#include <filesystem>

// 라이브러리 추가는 프로젝트에서 생성한 헤더보다 먼저 include하는게 좋음.
// 그렇지 않으면 먼저 나온 프로젝트 생성 헤더가 라이브러리에 필요한 정보를 먼저 사용하려고 하다가 에러날 수 있음.

// TransparentBlt가 구현되어있는 라이브러리 링크
#pragma comment(lib, "msimg32.lib")

// Sound 관련 라이브러리 추가
#include "mmsystem.h"
#include <dsound.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")


using std::vector;
using std::list;
using std::map;
using std::string;
using std::wstring;
using std::make_pair;

#include "define.h"
#include "Singleton.h"
#include "enum.h"
#include "struct.h"

#include "func.h"

#include "CSelectObj.h"
#include "CDbgRenderer.h"
#include "CEngine.h"


#endif //PCH_H
