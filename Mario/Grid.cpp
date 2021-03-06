#include "Grid.h"
#include "Mario.h"
#include "Camera.h"
#include "Items.h"
#include "Weapons.h"
#include "Effects.h"

Grid* Grid::__instance = NULL;
Grid::Grid() 
{
	
}
Area Grid::GetCell(RECT e)
{
	return {
		int(max(0		, e.top / SizeCell)),
		int(max(0		, e.left / SizeCell)),
		int(min(cols - 1, int(e.right / SizeCell))),
		int(min(rows - 1, int(e.bottom / SizeCell)))
	};
}

void Grid::Init()
{	
	Cells.clear();
	for (int y = 0; y < rows; ++y)
	{
		auto row = std::vector<Cell*>();
		for (int x = 0; x < cols; ++x)
		{
			row.push_back(new Cell(x, y));
		}
		Cells.push_back(row);
	}
	DebugOut(L"Cell %d %d\n", rows, cols);
}
void Grid::AddMovingObject(LPGAMEOBJECT obj, float x, float y)
{
	RECT e;
	e.top = y;
	e.left = x;
	e.right = x + obj->widthBBox;
	e.bottom = y + obj->heightBBox;
	obj->GetRect();
	auto area = GetCell(e);
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell) {
		Cells[r][c]->movingObjects.insert(obj);
		DebugOut(L"[INFO] object Moving TYPE: %d is add in Cell [%d] [%d]\n", obj->type, r, c);
	}
	obj->SetPosition(x, y);
}

void Grid::AddStaticObjectByFile(LPGAMEOBJECT obj, int Left, int Top, int Right, int Bottom)
{
	RECT e;
	e.top = Left;
	e.left = Top;
	e.right = Right;
	e.bottom = Bottom;
	auto area = GetCell(e);
	LOOP(r, Top, Bottom) {
		LOOP(c, Left, Right)
		{
			DebugOut(L"[INFO] object Static TYPE: %d is add in Cell [%d] [%d]\n", obj->type, r, c);
			Cells[r][c]->staticObjects.insert(obj);
		}
	}
}

void Grid::AddMovingObjectByFile(LPGAMEOBJECT obj, int Left, int Top, int Right, int Bottom)
{
	RECT e;
	e.top = Left;
	e.left = Top;
	e.right = Right;
	e.bottom = Bottom;
	auto area = GetCell(e);
	LOOP(r, Top, Bottom) {
		LOOP(c, Left, Right)
		{
			DebugOut(L"[INFO] object Static TYPE: %d is add in Cell [%d] [%d]\n", obj->type, r, c);
			Cells[r][c]->movingObjects.insert(obj);
		}
	}
}

void Grid::AddStaticObject(LPGAMEOBJECT obj, float x, float y)
{
	RECT e;
	e.top = y;
	e.left = x;
	e.right = x + obj->widthBBox;
	e.bottom = y + obj->heightBBox;
	auto area = GetCell(e);
	LOOP(r, area.TopCell, area.BottomCell) {
		LOOP(c, area.LeftCell, area.RightCell)
		{
			//DebugOut(L"[INFO] object Static TYPE: %d is add in Cell [%d] [%d]\n", obj->type, r, c);
			Cells[r][c]->staticObjects.insert(obj);
		}
	}
	obj->SetPosition(x, y);
}
void Grid::LoadObjects(LPGAMEOBJECT& obj, int Left, int Top, int Right, int Bottom)
{
	
	switch (obj->tag)
	{
	case GROUND:
	{
		AddStaticObjectByFile(obj, Left, Top,Right,Bottom);
		break;
	}
	case ENEMY:
	{
		AddMovingObjectByFile(obj, Left, Top, Right, Bottom);
		break;
	}
	case ITEM:
		AddStaticObjectByFile(obj, Left, Top, Right, Bottom);
		break;
	case BOX:
		AddStaticObjectByFile(obj, Left, Top, Right, Bottom);
		break;
	case EFFECT:
	{
		AddStaticObjectByFile(obj, Left, Top, Right, Bottom);
		break; 
	}
	default:
		DebugOut(L"[ERR] Invalid object TYPE: %d\n", obj->type);
		break;
	}
}


void Grid::RenderCell()
{
	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->Get(ID_TEX_BBOX);
	auto area = GetCell(camera->GetBBox());
	
	RECT rect;

	for (int r = area.TopCell; r <= area.BottomCell; r++)
	{
		for (int c = area.LeftCell; c <= area.RightCell; c++)
		{
			SetRect(&rect, 
					Cells[r][c]->posX * SizeCell,
					Cells[r][c]->posY * SizeCell, 
					Cells[r][c]->posX * SizeCell + SizeCell, 
					Cells[r][c]->posY * SizeCell + SizeCell);
			Game::GetInstance()->Draw(rect.left, rect.top, bbox, rect.left, rect.top, rect.left + SizeCell, rect.top + 1, 255);
			Game::GetInstance()->Draw(rect.left, rect.top, bbox, rect.left, rect.top, rect.left + 1, rect.top + SizeCell, 255);
			
		}
	}
}


void Grid::CalcObjectInViewPort()
{
	auto area = GetCell(camera->GetBBox());
	unordered_set<GameObject*> result;
	for(int r = area.TopCell;r <= area.BottomCell;r++)
	{
		//DebugOut(L"[info] Cell row [%d]\n", r);
		for(int c = area.LeftCell; c <= area.RightCell;c++)
		{
			result.insert(Cells[r][c]->movingObjects.begin(), Cells[r][c]->movingObjects.end());
			result.insert(Cells[r][c]->staticObjects.begin(), Cells[r][c]->staticObjects.end());
			//DebugOut(L"[info] Object in Cell  [%d]: %d\n",c,Cells[r][c]->staticObjects.size());
			//DebugOut(L"[info] Object move in Cell  [%d]: %d\n",c,Cells[r][c]->movingObjects.size());
			//DebugOut(L"[info] Cell column [%d]\n",c);
		}
	}
	CurObjectInViewPort = { result.begin(), result.end() };
	//DebugOut(L"[info] Cell left: [%d], top: [%d], right: [%d] bottom: [%d]\n", area.LeftCell, area.TopCell, area.RightCell, area.BottomCell);
	//DebugOut(L"[info] Object in viewport: %d\n", CurObjectInViewPort.size());
}

template<typename T, typename Pred>
void RemoveObjectIf(unordered_set<T>& container, Pred  del)
{
	for (auto it = container.begin(), end = container.end(); it != end; )
	{
		if (del(*it)) it = container.erase(it);
		else                       it++;
	}
}

void Grid::UpdateCellInViewPort()
{
	auto area = GetCell(camera->GetBBox());
	unordered_set<LPGAMEOBJECT> shouldBeUpdatedObjects;
	bool isDeadObject = false;
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell)
	{
		if (Cells[r][c]->movingObjects.size() == 0) continue;
		//DebugOut(L"Obj in cell [%d] %d\n", c, Cells[r][c]->movingObjects.size());
		RemoveObjectIf(Cells[r][c]->movingObjects, [&](auto& obj)
		{
				RECT e;
				e.left = obj->x;
				e.top = obj->y;
				e.right = obj->x + obj->widthBBox;
				e.bottom = obj->y + obj->heightBBox;
				auto objArea = GetCell(e);
				if (obj->canDel) isDeadObject = true;
				if (objArea.TopCell != r || objArea.RightCell != c)
				{
					//DebugOut(L"obj in cell [%d]\n", c);
					shouldBeUpdatedObjects.emplace(obj);
					return true;
				}
				return false;
		});
	}
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell)
	{
		if (Cells[r][c]->staticObjects.size() == 0) continue;
		//DebugOut(L"Obj in cell [%d] %d\n", c, Cells[r][c]->movingObjects.size());
		RemoveObjectIf(Cells[r][c]->staticObjects, [&](auto& obj)
			{
				RECT e;
				e.left = obj->x;
				e.top = obj->y;
				e.right = obj->x + obj->widthBBox;
				e.bottom = obj->y + obj->heightBBox;
				auto objArea = GetCell(e);
				if (obj->canDel)
				{
					return true;
					//isDeadObject = true;
				}
				return false;
			});
	}
	for (auto& obj : shouldBeUpdatedObjects)
	{
		RECT e;
		e.left = obj->x;
		e.top = obj->y;	
		e.right = obj->x + obj->widthBBox;
		e.bottom = obj->y + obj->heightBBox;
		auto objArea = GetCell(e);
		LOOP(r, objArea.TopCell, objArea.BottomCell)
			LOOP(c, objArea.LeftCell, objArea.RightCell)
			{
				Cells[r][c]->movingObjects.emplace(obj);
				//DebugOut(L"obj move to %d   \n",c);
			}
	}
	if (isDeadObject) RemoveDeadObject();
	CalcObjectInViewPort();

}




void Grid::RemoveDeadObject() 
{
	auto area = GetCell(camera->GetBBox());
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell)
	{
		RemoveObjectIf(Cells[r][c]->movingObjects, [](auto obj) {return obj->canDel; });
	}
}

Grid* Grid::GetInstance()
{
	if (__instance == NULL)
		__instance = new Grid();
	return __instance;
}