#include <iostream>
using namespace std;

# define input_file "NguyenNgocTiep_2280619056.txt"
#define MAX 100
#define VOCUC 1000

template <typename Function>
void tinhThoiGian(Function func);

typedef struct GRAPH{
    int n;
    int a[MAX][MAX];
}DOTHI;
int DocMaTranKe(const char TenFile[], DOTHI &g)
{
    FILE* f;
    f = fopen(TenFile, "rt");

    if(f == NULL) {
        return 0;
    }
    fscanf(f, "%d", &g.n);
    int huong;
    fscanf(f, "%d", &huong);
    for(int i = 0; i < g.n; i++)
    {
        for(int j = 0; j < g.n; j++)
        {
            int row;
            int col;
            int weight;

            fscanf(f, "%d", &row);
            fscanf(f, "%d", &col);
            fscanf(f, "%d", &weight);

            g.a[row][col] = weight;
            if(huong==0)
                g.a[col][row] = weight;  
        }
    }
    return 1;
    fclose(f);
}
void XuatMaTranKe(DOTHI g)
{
    cout << g.n << endl;
    for(int i = 0; i < g.n; i++)
    {
        for(int j = 0; j < g.n; j++)
        {
            cout << g.a[i][j] << " ";
        }
        cout << endl;
    }
}
bool LaVoHuong(DOTHI g)
{
    for(int i = 0; i < g.n; i++)
    {
        for(int j = 0; j < g.n; j++)
        {
            if(g.a[i][j] != g.a[j][i])
            {
                return false;
            }
        }
    }
    return true;
}

bool CoKhuuyen(DOTHI g)
{
    for(int i = 0; i < g.n; i++)
    {
       if(g.a[i][i] != 0)
        return true;
    }
    return false;
}

//==============================================================
//Kiem tra chu trinh-duong di
typedef struct STACK{
    int array[MAX];
    int size;
}STACK;
void khoitaostack(STACK &stack)
{
    stack.size = 0;
}
void DayGiaTriVaoStack (STACK &stack, int value)
{
    if(stack.size < MAX)
    {
        stack.array[stack.size] = value;
        stack.size++;
    }
}

int bacCuaDinh(DOTHI g, int dinh)
{
     int bac = 0;
    for(int i = 0; i < g.n; i++)
    {
        if(g.a[dinh][i] != 0){
            if(dinh == i)
                bac+=2;
        	else bac++;
        }
    }
    return bac;
}
void DuaVaoStack(STACK &stack, int value)
{
    if(stack.size < MAX)
    {
        stack.array[stack.size] = value;
        stack.size++;
	}
}
void TimDuongDi(int i, DOTHI &g, STACK &stack){
    for(int j = 0; j < g.n; j++)
    {
        if(g.a[i][j] != 0)
        {
			g.a[i][j] = g.a[j][i] = 0;
            TimDuongDi(j, g, stack);
        }
    }
    DuaVaoStack(stack, i);
}
int KiemTraDuongDiEuler(DOTHI g)
{
    STACK stack;
    int x = 0;
    //Kiem tra bac cua cac dinh
    int dem = 0;
    for(int i = 0; i < g.n; i++)
    {
        if(bacCuaDinh(g, i) % 2 != 0)
        {
			dem++;
            x = i;
        }
    }
    if(dem!=2 && dem!= 0) return 0;
    DOTHI temp = g;
    TimDuongDi(x, temp, stack);
    
    for(int i = 0; i < temp.n; i++)
        for(int j = 0; j < temp.n; j++)
            if(temp.a[i][j] !=0 || temp.a[j][i] != 0) return 0;
    cout << "Duong di Euler la " << endl;
    while(stack.size != 0)
    {
        cout << stack.array[--stack.size]<< " ";
    }
    cout << endl;
    return 1;
}
///chu trinh


void diTimDoThi(int i, DOTHI &g, STACK &stack){
    for(int j = 0; j < g.n; j++)
    {
        if(g.a[i][j] != 0)
        {
			g.a[i][j] = g.a[j][i] = 0;
            diTimDoThi(j, g, stack);
        }
    }
    DuaVaoStack(stack, i);
}
int KiemTraChuTrinhEuler(DOTHI g)
{
    STACK stack;
    int x = 0;
    //Kiem tra bac cua cac dinh
    for(int i = 0; i < g.n; i++)
    {
        if(bacCuaDinh(g, i) % 2 != 0) return 0;
    }
    DOTHI temp = g;
    diTimDoThi(x, temp, stack);
    
    for(int i = 0; i < temp.n; i++)
        for(int j = 0; j < temp.n; j++)
            if(temp.a[i][j] !=0 || temp.a[j][i] != 0) return 0;
    if(stack.array[0] != stack.array[stack.size-1]) return 0;
    cout << "Chu trinh Euler la " << endl;
    while(stack.size != 0)
    {
        cout << stack.array[--stack.size] << " ";
    }
    return 1;
}
//===================================================================
//Cay khung nho nhat
void timDinhLienThong(DOTHI &g, int nhan[MAX], int i)
{
    for(int j = 0;j < g.n; j++)
    {
        if(g.a[i][j] != 0 && nhan[i] != nhan[j])
        {
            nhan[j] = nhan[i];
            timDinhLienThong(g, nhan, j);
        }
    }
}
int soTPLienThong(DOTHI &g)
{
    int SoTPLT = 0, nhan[MAX];
    for(int i = 0; i < g.n; i++) nhan[i] = 0;

    for(int i = 0; i < g.n ;i++){
        if(nhan[i] == 0)
            SoTPLT ++;
            nhan[i] = SoTPLT;
            timDinhLienThong(g, nhan, i);
    }
    return SoTPLT;
}
int ChuaXet[MAX];

typedef struct EDGE {
    int u, v, value;
}CANH;

CANH T[MAX];

void Prim(DOTHI g)
{
    if(soTPLienThong(g) != 1)
    {
        cout << "Do thi khong lien thong, dung thuat toan Prim \n" << endl;
        return;
    }
    int nT = 0;
    for(int i = 0; i < g.n; i++)
    {
        ChuaXet[i] = 0;
    }
    ChuaXet[0] = 1;
    while(nT < g.n - 1)
    {
        CANH CanhNhoNhat;
        int GiaTriNhoNhat = 1000;
        for(int i = 0; i < g.n; i++)
            if(ChuaXet[i] == 1)
            {
                for(int j = 0; j < g.n; j++)
                {
                    if(ChuaXet[j] == 0 && g.a[i][j] != 0 && GiaTriNhoNhat > g.a[i][j]){
                        CanhNhoNhat.u = i; CanhNhoNhat.v = j;
                        CanhNhoNhat.value = g.a[i][j];
                        GiaTriNhoNhat = g.a[i][j];
                    }
                }
            }   
        T[nT++] = CanhNhoNhat;
        ChuaXet[CanhNhoNhat.v] = 1;   
    }

    cout << "Cay khung nho nhat cua do thi la\n";
    for(int i = 0; i < nT - 1; i++)
    {
        printf("(%d, %d),  ", T[i].u, T[i].v);
    }
}

//////Kruskal

void SapXepTang(CANH E[100], int tongsocanh)
{
    for(int i = 0; i < tongsocanh - 1; i++)
    {
        for(int j = i+1; j < tongsocanh; j++)
        {
            if(E[i].value > E[j].value)
            {
                CANH tmp = E[i];
                E[i] = E[j];
                E[j] = tmp;
            }
        }

    }
}
void Kruskal(DOTHI g)
{
    CANH listEdge[MAX];
    int tongsocanh = 0;

    for(int i = 0; i < g.n; i++)
    {
        for(int j = i+1; j < g.n; j++)
        {
            if(g.a[i][j] > 0)
            {
                listEdge[tongsocanh].u = i;
                listEdge[tongsocanh].v = j;
                listEdge[tongsocanh].value = g.a[i][j];
                tongsocanh++;
            }
        }
    }
    SapXepTang(listEdge, tongsocanh);
    int nT = 0;
    CANH T[MAX];
    int nhan[MAX];
    for(int i = 0; i < g.n; i++)
    {
        nhan[i] = i;
    }
    int canhdangxet = 0;
    while(nT < g.n && canhdangxet < tongsocanh){
        CANH edge = listEdge[canhdangxet];
        int u = nhan[edge.u], v = nhan[edge.v];
        if(u != v)
        {
            T[nT++] = edge;
            for(int j = 0; j < g.n; j++)
                if(nhan[j] == v) nhan[j] = u;
        }
        canhdangxet++;
    }
    if(nT != g.n - 1) printf("\nDo thi khong co cay khung\n");
    else{
        cout << "\nCay khung nho nhat dung Kruskal la " << endl;
        for(int i = 0; i < nT; i++)
        {
            printf("(%d, %d), ", T[i].u, T[i].v);
        }
    }
}
//============================================================
//Tim duon di ngan nhat dijkstra, floyd
int Sau_Nut[MAX][MAX];
int L[MAX][MAX];

void Floyd(DOTHI g){
    for(int i = 0; i < g.n; i++)
    {
        for(int j = 0; j < g.n; j++)
        {
            if(g.a[i][j] > 0){
                Sau_Nut[i][j] = j;
                
                L[i][j] = g.a[i][j];
            }
            else {
                Sau_Nut[i][j] = -1;
                L[i][j] = VOCUC;
        	}
		}
        
    }
    
    for(int k = 0; k < g.n; k++)
    {
        for(int i = 0; i < g.n; i++)
        {
            for(int j = 0; j < g.n; j++)
            {
                if(L[i][j] > L[i][k] + L[k][j]){
                    L[i][j] = L[i][k] + L[k][j];
                    Sau_Nut[i][j] = Sau_Nut[i][k];
                }
			}
        }
    }

    int S, F;
    cout << "\nNhap dinh S : ";
    cin >> S;
    cout << "Nhap dinh F : ";
    cin >> F;
    if(Sau_Nut[S][F] == -1)
        printf("-1");
    else {
        printf("%d\n", L[S][F]);
        printf("%d ", S);
        int u = S;
        while(Sau_Nut[u][F] != F){
            u = Sau_Nut[u][F];
            printf("%d ", u);
        }
        printf("%d", F);   
    }
    
}
// Dijkstra
int LuuVet[MAX];
int DoDaiDuongDiToi[MAX];

int TimDuongDiNhoNhat(DOTHI g)
{
    int li = -1;
    int p = VOCUC;  
    for(int i = 0; i < g.n; i++)
    {
        if(ChuaXet[i] == 0 && DoDaiDuongDiToi[i] < p)
        {
            p = DoDaiDuongDiToi[i];
            li = i;
        }
    }
    return li;
}
void CapNhatDuongDi(int u, DOTHI g)
{
    ChuaXet[u] = 1;
    for(int v = 0; v < g.n; v++)
    {
        if(ChuaXet[v] == 0 && g.a[u][v] > 0 && g.a[u][v] < VOCUC)
        {
            if(DoDaiDuongDiToi[v] > DoDaiDuongDiToi[u] + g.a[u][v])
            {
                DoDaiDuongDiToi[v]  = DoDaiDuongDiToi[u] + g.a[u][v];
                LuuVet[v] = u;
            }
        }
    }
}
void Dijkstra(int s, int F, DOTHI g)
{
    for(int i = 0; i < g.n; i++)
    {
        ChuaXet[i] = 0;
        DoDaiDuongDiToi[i] = VOCUC;
        LuuVet[i] = -1;
    }
    DoDaiDuongDiToi[s] = 0;
    while(ChuaXet[F] == 0)
    {
        int u = TimDuongDiNhoNhat(g);
        if(u == -1)
            break;
        CapNhatDuongDi(u, g);
    }
    if(ChuaXet[F] == 1)
    {
        printf("Duong di ngan nhat tu [%d] den [%d] la : \n\t", s, F);
        printf("%d ", F);
        int i = LuuVet[F];
        while(i != -1)
        {
            printf("<- %d ", i);
            i = LuuVet[i];
        }
        cout << endl;
        printf("\tVoi do dai la %d\n", DoDaiDuongDiToi[F]);
    }
    else printf("Khong co duong di tu dinh %d den dinh %d \n", s, F);
}
void chucNang()
{
    cout << endl;
    cout << "--------------------Menu-----------------" << endl;
    cout << "Bam phim 1 : Xuat ma tran ke/trong so" << endl;
    cout << "Bam phim 2 : Kiem tra do thi vo huong" << endl;
    cout << "Bam phim 3 : Kiem tra chu trinh va duong di Euler" << endl;
    cout << "Bam phim 4 : Tim cay khung nho nhat bang Prim hoac Kruskal" << endl;
    cout << "Bam phim 5 : Tim duong di ngan nhat bang Dijktra hoac Floyd" << endl;
}
int main()
{
    DOTHI g;
    
   
    if(DocMaTranKe(input_file, g)==1)
    {
        XuatMaTranKe(g);
    }
    else cout << "Doc file that bai" << endl;

    if(LaVoHuong(g))   
        cout << "La do thi vo huong" << endl;
    else cout << "Khong la do thi vo huong" << endl;

    if(CoKhuuyen(g)) cout << "Do thi co khuyen" << endl;
    else cout << "Do thi khong co khuyen" << endl;

    if(KiemTraChuTrinhEuler(g)==0)
        cout << "Khong co chu trinh Euler" << endl;

    if(KiemTraDuongDiEuler(g)==0)
        cout << "Khong duong di Euler" << endl;

    Prim(g);
    int s;
    int f;
    cout << "\nNhap s : ";
    cin >> s;
    cout << "Nhap f : ";
    cin >> f;
    Dijkstra(s, f, g);
    Kruskal(g);

    ///////////
    auto start = std::chrono::high_resolution_clock::now();

    // Gọi hàm cần đo thời gian
    Floyd(g);

    // Lấy thời điểm kết thúc
    auto end = std::chrono::high_resolution_clock::now();

    // Tính khoảng thời gian giữa hai thời điểm
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // In ra thời gian chạy của hàm
    std::cout << "\nTime taken by function: " << duration.count() << " microseconds" << std::endl;    
}

