// ---------------------------------------------------------------------------

#include <vcl.h>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <queue>
#pragma hdrstop

#include "Unit2.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;

TForm2 *Form2;
int n, m, kol;

Graphics::TBitmap *open = new Graphics::TBitmap();
Graphics::TBitmap *cl = new Graphics::TBitmap();
Graphics::TBitmap *normal = new Graphics::TBitmap();
Graphics::TBitmap *flag = new Graphics::TBitmap();
Graphics::TBitmap *boom = new Graphics::TBitmap();

Graphics::TBitmap *one = new Graphics::TBitmap();
Graphics::TBitmap *two = new Graphics::TBitmap();
Graphics::TBitmap *three = new Graphics::TBitmap();
Graphics::TBitmap *four = new Graphics::TBitmap();
Graphics::TBitmap *five = new Graphics::TBitmap();
Graphics::TBitmap *six = new Graphics::TBitmap();
Graphics::TBitmap *seven = new Graphics::TBitmap();
Graphics::TBitmap *eight = new Graphics::TBitmap();


class GameBoard{
	int row, column;
	vector<vector<int>> pole;
	vector<vector<int>> used;
	vector<int>dx = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	vector<int>dy = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

	public:
		void generate(int n, int m);

};

void GameBoard::generate(int n, int m){

}


vector<vector<int>> a;

vector<vector<int>> used;

int ans = 0;

vector<int>dx = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
vector<int>dy = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

// ---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender) {

	srand(time(0));

	m = StrToInt(LabeledEdit1->Text);
	n = StrToInt(LabeledEdit2->Text);
	kol = StrToInt(LabeledEdit3->Text);
	DrawGrid1->RowCount = n;
	DrawGrid1->ColCount = m;

	DrawGrid1->Height = n * 40 + 5;///555
	DrawGrid1->Width = m * 40 + 5;///555
	// Form2->Height = DrawGrid1->Height + 4 * DrawGrid1->DefaultRowHeight;
	// Form2->Width = DrawGrid1->Width + DrawGrid1->DefaultColWidth;

	ans = 0;

	vector<vector<int> >ab(m, vector<int>(n, 0));
	vector<vector<int> >us(m, vector<int>(n, -2));
	a = ab;
	used = us;
	DrawGrid1->Visible = true;
	///	DrawGrid1->Refresh();

	for (int i = 0; i < kol; i++) {
		bool flag = true;
		while (flag) {
			int x = rand() % m;
			int y = rand() % n;
			if (a[x][y] != -1) {
				flag = false;
				a[x][y] = -1;

				for (int j = 0; j < 9; j++) {
					int nx = x + dx[j];
					int ny = y + dy[j];
					if (nx >= 0 && nx < m && ny >= 0 && ny <
						n && a[nx][ny] != -1)
						a[nx][ny]++;
				}
			}
		}
	}

	DrawGrid1->Refresh();
}
// ---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender) {
	open->LoadFromFile("open.bmp");
	cl->LoadFromFile("клетка.bmp");
	normal->LoadFromFile("normal.bmp");
	flag->LoadFromFile("flag.bmp");
	boom->LoadFromFile("boom1.bmp");

	one->LoadFromFile("1.bmp");
	two->LoadFromFile("2.bmp");
	three->LoadFromFile("3.bmp");
	four->LoadFromFile("4.bmp");
	five->LoadFromFile("5.bmp");
	six->LoadFromFile("6.bmp");
	seven->LoadFromFile("7.bmp");
	eight->LoadFromFile("8.bmp");
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::DrawGrid1DrawCell(TObject *Sender, int ACol, int ARow,
	TRect &Rect, TGridDrawState State) {
	int x = ACol;
	int y = ARow;

	if (used[x][y] == -2) {
		DrawGrid1->Canvas->StretchDraw(Rect, cl);
	}
	else {
		bool fla = true;
		if (used[x][y] == 9) {
			DrawGrid1->Canvas->StretchDraw(Rect, boom);
			ShowMessage("You exploded!");
			Close();
		}
		if (used[x][y] == -1) {
			DrawGrid1->Canvas->StretchDraw(Rect, normal);
			fla = false;
		}
		if (used[x][y] == 0) {
			DrawGrid1->Canvas->StretchDraw(Rect, open);
			fla = false;
		}
		if (used[x][y] == 1) {
			DrawGrid1->Canvas->StretchDraw(Rect, one);
			fla = false;
		}
		if (used[x][y] == 2) {
			DrawGrid1->Canvas->StretchDraw(Rect, two);
			fla = false;
		}
		if (used[x][y] == 3) {
			DrawGrid1->Canvas->StretchDraw(Rect, three);
			fla = false;
		}
		if (used[x][y] == 4) {
			DrawGrid1->Canvas->StretchDraw(Rect, four);
			fla = false;
		}
		if (used[x][y] == 5) {
			DrawGrid1->Canvas->StretchDraw(Rect, five);
			fla = false;
		}
		if (used[x][y] == 6) {
			DrawGrid1->Canvas->StretchDraw(Rect, six);
			fla = false;
		}
		if (used[x][y] == 7) {
			DrawGrid1->Canvas->StretchDraw(Rect, seven);
			fla = false;
		}
		if (used[x][y] == 8) {
			DrawGrid1->Canvas->StretchDraw(Rect, eight);
			fla = false;
		}
		if (used[x][y] == 11) {
			DrawGrid1->Canvas->StretchDraw(Rect, flag);
			fla = false;
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::DrawGrid1SelectCell(TObject *Sender, int ACol, int ARow,
	bool &CanSelect) {
	int xe = ACol;
	int ye = ARow;
	used[xe][ye] = a[xe][ye];
	if (a[xe][ye] == 0) {
		queue < pair < int, int >> q;
		q.push({xe, ye});
		while (!q.empty()) {
			pair<int, int>koor = q.front();
			int x = koor.first;
			int y = koor.second;
			q.pop();
			used[x][y] = 0;
			for (int j = 0; j < 9; j++) {
				int nx = x + dx[j];
				int ny = y + dy[j];
				if (nx >= 0 && nx < m && ny >= 0 && ny <
					n && used[nx][ny] == -2) {
					if (a[nx][ny] == 0) {
						q.push({nx, ny});
					}
					else {
						used[nx][ny] = a[nx][ny];
					}
				}
			}
		}

	}
	if (a[xe][ye] == -1) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++)
				used[i][j] = a[i][j];
		}
		used[xe][ye] = 9;

	}
	DrawGrid1->Refresh();
}
// ---------------------------------------------------------------------------

void __fastcall TForm2::DrawGrid1MouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y) {
	if (Button == mbRight) {
		int xe = X / 40;
		int ye = Y / 40;
		if (used[xe][ye] != 11) {
			used[xe][ye] = 11;
			if (a[xe][ye] == -1) {
				ans++;
			}
		}
		else{
			used[xe][ye] = -2;
			if (a[xe][ye] == -1) {
				ans--;
			}
		}

	}
	DrawGrid1->Refresh();
	if (ans == kol) {
		int close_kol = 0;
		for(int i = 0;i<m;i++)
		{
			for(int j = 0;j<n;j++)
			{
				if(used[i][j]==-2)
					close_kol++;
            }
		}
		if(close_kol==0){
			ShowMessage("Win!!!");
			Close();
		}
		DrawGrid1->Refresh();
    }
}
// ---------------------------------------------------------------------------
