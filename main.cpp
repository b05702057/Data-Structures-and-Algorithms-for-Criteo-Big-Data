//
//  main.cpp
//  作業二
//
//  Created by 李季澄 on 2020/4/10.
//  Copyright © 2020 李季澄. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

const int datalimit = 15995634 ; // 資料筆數

void get(string u, string p, string t, vector< vector<string> > &upt_array_2D) // binary search，如果有找到就輸出1，否則輸出0
{
    int mid = static_cast<int>(upt_array_2D.size()) / 2, low = 0, high = static_cast<int>(upt_array_2D.size()) - 1 ;
    vector<string> upt_target(3, "0") ;
    upt_target[0] = u ;
    upt_target[1] = p ;
    upt_target[2] = t ;
    vector<string> upt_now(3, "0") ;
    bool found = false ;
    while(low <= high)
    {
        mid = (low + high) / 2 ;
        upt_now[0] = upt_array_2D[mid][0] ;
        upt_now[1] = upt_array_2D[mid][1] ;
        upt_now[2] = upt_array_2D[mid][2] ;
        
        if (upt_now > upt_target)
            high = mid - 1 ;
        
        else if (upt_now < upt_target)
            low = mid + 1 ;

        
        else // 確定只有一種可能
        {
            cout << "1" << endl ;
            found = true ;
            break ;
        }
    }
    if (found == false)
        cout << "0" << endl ;
}

void purchased(string u, vector< vector<string> > &upt_array_2D) // 找到第一個出現的u，再依序輸出該u的購買資料
{
    int mid = static_cast<int>(upt_array_2D.size()) / 2, low = 0, high = static_cast<int>(upt_array_2D.size()) - 1 ;
    while(low <= high) // 不一定有買
    {
        mid = (low + high) / 2 ;
        if(upt_array_2D[mid][0] > u) // 比target大
            high = mid - 1 ;
        else if(upt_array_2D[mid][0] < u) // 比target小
            low = mid + 1 ;
        else // 雖然找到，但可能不是第一筆u
        {
            if(mid - 1 >= 0 and upt_array_2D[mid-1][0] == u) // 比target大
                high = mid - 1 ;
            else // 就是target
            {
                int index = mid ;
                while(true)
                {
                    cout << upt_array_2D[index][1] << " " << upt_array_2D[index][2] << " " << upt_array_2D[index][3] << " " <<  upt_array_2D[index][4] << " " << upt_array_2D[index][5] << endl ;
                    if (index == datalimit - 1)
                        break ;
                    index += 1 ;
                    if (upt_array_2D[index][0] != u)
                        break ;
                }
                break ;
            }
        }
    }
}

void clicked(string p1, string p2, vector< vector<string> > &set_pu_array_2D) // p1及p2一定存在
{
    int mid = static_cast<int>(set_pu_array_2D.size()) / 2, low = 0, high = static_cast<int>(set_pu_array_2D.size()) - 1 ;
    while (true)
    {
        mid = (low + high) / 2 ;
        if (set_pu_array_2D[mid][0] > p1) // 比target大
            high = mid - 1 ;
        else if (set_pu_array_2D[mid][0] < p1) // 比target小
            low = mid + 1 ;
        else
        {
            if (mid - 1 >= 0 and set_pu_array_2D[mid-1][0] == p1) // 比target大
                high = mid - 1 ;
            else // 找到target，此時mid為target的index
                break ;
        }
    } // 先找到有點擊p1的第一位user（此陣列不重複）
    int index = mid ; // p1出現的第一列
    vector<string> p2u_target(2, "0") ;
    p2u_target[0] = p2 ; // p2不變
    while(true) // 找此user是否有同時點擊p2
    {
        p2u_target[1] = set_pu_array_2D[index][1] ; // target中只有u會變動
        mid = static_cast<int>(set_pu_array_2D.size()) / 2 ; // 初始化
        low = 0 ;
        high = static_cast<int>(set_pu_array_2D.size()) - 1 ;
        
        while(low <= high) // 不一定找得到p2與u的組合
        {
            mid = (low + high) / 2 ; // 先更新mid，再更新矩陣
            vector<string> p2u_now(2, "0") ;
            p2u_now[0] = set_pu_array_2D[mid][0] ; // p
            p2u_now[1] = set_pu_array_2D[mid][1] ; // u
            if (p2u_now > p2u_target)
                high = mid - 1 ;
            else if (p2u_now < p2u_target)
                low = mid + 1 ;
            else
            {
                cout << set_pu_array_2D[mid][1] << endl ;
                break ;
            }
        }
        index += 1 ; // 找下一個u
        if (set_pu_array_2D[index][0] != p1) // p1已無user
            break ;
    }
}


// 先從set_t_1u中找到第一個符合條件的t，再透過binary search找u在時間區段內的累積次數
void profit(string t, string theata, vector<string> &set_u_array_1D, vector< vector<string> > &set_ut_array_2D, vector< vector<string> > & set_u1_t_array_2D)
{
    if (theata == "0")
    {
        for (int i = 0; i <= 9; i ++)
            cout << set_u_array_1D[i] << endl ; // 直接輸出前十個u
    }
    else if (set_u1_t_array_2D[set_u1_t_array_2D.size()-1][0] >= t) // theata不為0，且有時間比t大
    {
        int cout_num = 0 ;
        string u ; // 正在找的user
        vector<string> ut_target(2, "0") ;
        ut_target[1] = t ; // 要找該u中大於等於t的第一筆資料
        vector<string> ut_now(2, "0") ;
        vector<string> ut_prev(2, "0") ;
        int mid = static_cast<int>(set_ut_array_2D.size()) / 2, low = 0, high = static_cast<int>(set_ut_array_2D.size()) - 1 ;
        for (int i = 0; i <= set_u1_t_array_2D.size() - 1; i++) // 從最小的u開始
        {
            if (set_u1_t_array_2D[i][1] >= t) // 該u有在t之後點擊才要檢查
            {
                ut_target[0] = set_u1_t_array_2D[i][0] ; // u
                low = 0 ; // 重置
                high = static_cast<int>(set_ut_array_2D.size()) - 1 ;
                while(true)
                {
                    mid = (low + high) / 2 ;
                    ut_now[0] = set_ut_array_2D[mid][0] ;
                    ut_now[1] = set_ut_array_2D[mid][1] ;
                    if (ut_now >= ut_target) // 大於等於target
                    {
                        if (mid - 1 >= 0)
                        {
                            ut_prev[0] = set_ut_array_2D[mid-1][0] ;
                            ut_prev[1] = set_ut_array_2D[mid-1][1] ;
                            if (ut_prev >= ut_target)
                                high = mid - 1 ;
                            else // 前一個比target小，這個大於等於target
                            {
                                if (stof(set_ut_array_2D[mid][3]) / stof(set_ut_array_2D[mid][2]) >= stof(theata))
                                {
                                    cout << set_ut_array_2D[mid][0] << endl ;
                                    cout_num += 1 ;
                                }
                                break ;
                            }
                        }
                        else // 就是target
                        {
                            if (stof(set_ut_array_2D[mid][3]) / stof(set_ut_array_2D[mid][2]) >= stof(theata))
                            {
                                cout << set_ut_array_2D[mid][0] << endl ;
                                cout_num += 1 ;
                            }
                            break ;
                        }
                    }
                    else // 小於target
                        low = mid + 1 ;
                }
                if (cout_num == 10)
                    break ;
            }
        }
    }
}

 
int main(int argc, char** argv)
{
//    clock_t start, stop;
//    start = clock(); // 開始計時

    ifstream inFile(argv[1]) ; // 輸入檔案位置
//int main()
//{
//    clock_t start, stop;
//    start = clock(); // 開始計時
//    ifstream inFile("/Users/lijicheng/Downloads/資料結構與演算法/hw2/Criteo_Conversion_Search/CriteoSearchData") ;
    string line, u, p, t, s, price, age, gender ;
    vector<string> upt_row(6, "0") ; // u_id, p_id, click_time, price, age_group, gender
    vector< vector<string> > upt_array_2D(0, upt_row) ; // 用push_back處理
    vector<string> pu_row(2, "0") ; // 先建pu就好，等排除重複的再建up並sort
    vector< vector<string> > pu_array_2D(datalimit, pu_row) ;
    vector<string> uts_row(3, "0") ; // 還要裝sale的相關資訊
    vector< vector<string> > uts_array_2D(datalimit, uts_row) ;
    
    int line_num = 0 ; // 資料筆數
    while(getline(inFile,line))
    {
        int begin = 0, element_num = 0 ;
        for(int i = 0; i <= line.size() - 1; i++)
        {
            if (line.substr(i, 1) == "\t")
            {
                if (element_num == 19)
                    p = line.substr(begin, i - begin) ;
                else if (element_num == 3)
                    t = line.substr(begin, i - begin) ;
                else if (element_num == 0)
                    s = line.substr(begin, i - begin) ;
                else if (element_num == 5)
                    price = line.substr(begin, i - begin) ;
                else if (element_num == 6)
                    age = line.substr(begin, i - begin) ;
                else if (element_num == 9)
                    gender = line.substr(begin, i - begin) ;
                begin = i + 1 ; // 字頭
                element_num += 1 ; // 一開始從3裝起
            }
        }
        u = line.substr(begin, line.size() - begin) ; // u
        if (s == "1")
        {
            upt_row[0] = u ;
            upt_row[1] = p ;
            upt_row[2] = t ;
            upt_row[3] = price ;
            upt_row[4] = age ;
            upt_row[5] = gender ;
            upt_array_2D.push_back(upt_row) ;
        }
        pu_row[0] = p ;
        pu_row[1] = u ;
        pu_array_2D[line_num] = pu_row ;
        
        uts_row[0] = u ;
        uts_row[1] = t ;
        uts_row[2] = s ;
        uts_array_2D[line_num] = uts_row ;
        
        line_num += 1 ;
        if (line_num == datalimit)
            break ;
//        if (line_num % 1000000 == 0) // 確認進度
//            cout << line_num << " " ;
    }
    inFile.close(); // 已將所有資料填裝完畢
    
//
//    stop = clock(); // 結束計時
//    cout << double(stop - start) / CLOCKS_PER_SEC << " seconds" << endl;
    
    
    sort(upt_array_2D.begin(), upt_array_2D.end()) ; // upt_array排序完畢
    
    
//    stop = clock(); // 結束計時
//    cout << double(stop - start) / CLOCKS_PER_SEC << " seconds1" << endl;
    
    sort(pu_array_2D.begin(), pu_array_2D.end()) ; // pu_array排序完畢
    vector< vector<string> > set_pu_array_2D(1, pu_array_2D[0]) ; // 創造一個沒有重複元素的pu陣列，此先將第一列裝入
    for (int i = 1; i <= datalimit - 1; i++) // 從第二個開始（此作法和set的速度幾乎一樣）
    {
        if (pu_array_2D[i] != pu_array_2D[i-1])
            set_pu_array_2D.push_back(pu_array_2D[i]) ;
    }
    pu_array_2D.clear() ; // 不會再用到此陣列，因此釋放空間
    

//    stop = clock(); // 結束計時
//    cout << double(stop - start) / CLOCKS_PER_SEC << " seconds2" << endl;
    
    
    sort(uts_array_2D.begin(), uts_array_2D.end()) ;
    
    
//    stop = clock(); // 結束計時
//    cout << double(stop - start) / CLOCKS_PER_SEC << " seconds3" << endl;
    
    vector<string> set_u_array_1D(10, uts_array_2D[0][0]) ; // 為了profit函數，theata為0的情況
    int num_theata = 1 ;
    for (int i = 1; i <= datalimit - 1; i++) // 從1開始
    {
        if (uts_array_2D[i][0] != uts_array_2D[i-1][0]) // 和前一個不同
        {
            set_u_array_1D[num_theata] = uts_array_2D[i][0] ;
            num_theata += 1 ;
            if (num_theata == 10) // profit函數只要求10個user_id
                break ;
        }
    }
    
    string user = uts_array_2D[uts_array_2D.size()-1][0] ; // 從最後往前累加
    int total_num = 0, sale_num = 0 ;
    for (int i = datalimit - 1 ; i >= 0; i--) // 紀錄交易、點擊筆數
    {
        if (user != uts_array_2D[i][0]) // 變成下一個user
        {
            user = uts_array_2D[i][0] ; // 重新開始累加
            total_num = 0 ;
            sale_num = 0 ;
        }

        if (uts_array_2D[i][2] == "1")
            sale_num += 1 ;
        total_num += 1 ;
        uts_array_2D[i][2] = to_string(total_num) ;
        uts_array_2D[i].push_back(to_string(sale_num)) ;
    }
   
    vector< vector<string> > set_ut_array_2D ; // 找到符合的u後，必須找它多個t中的的第一個t（因此建立一個不重複tu的陣列）
    if (uts_array_2D[0][3] != "0")  // 先裝入第一個
        set_ut_array_2D.push_back(uts_array_2D[0]) ;
    for (int i = 1; i <= datalimit - 1; i++) // total_sale_num不為0且並非同一組tu（不用重新排序）
    {// total_sale_num不為0
        if (uts_array_2D[i][3] != "0" and (uts_array_2D[i][0] != uts_array_2D[i-1][0] or uts_array_2D[i][1] != uts_array_2D[i-1][1]))
                set_ut_array_2D.push_back(uts_array_2D[i]) ;
    }
    uts_array_2D.clear() ; // 已用不到此資料
    
    int length = static_cast<int>(set_ut_array_2D.size()) ;
    vector< vector<string> > set_u1_t_array_2D(0, set_ut_array_2D[length-1]) ; // 創造沒有重複u的陣列（取最大t)
    vector<string> u1t_row(2, "0") ;
    if (set_ut_array_2D[length-1][3] != "0")
    {
        u1t_row[0] = set_ut_array_2D[length-1][0] ;
        u1t_row[1] = set_ut_array_2D[length-1][1] ;
        set_u1_t_array_2D.push_back(u1t_row) ;
    }
    for (int i = length - 2; i >= 0; i--)
    {
        if (set_ut_array_2D[i][0] != set_ut_array_2D[i+1][0]) // u不重複
        {
            u1t_row[0] = set_ut_array_2D[i][0] ;
            u1t_row[1] = set_ut_array_2D[i][1] ;
            set_u1_t_array_2D.push_back(u1t_row) ;
        }
    }
    reverse(set_u1_t_array_2D.begin(), set_u1_t_array_2D.end()) ; // 因為是透過push_back放入，此時要倒轉
    
//    get("493CFB4A87C50804C94C0CF76ABD19CD", "A66DB02AC1726A8D79C518B7F7AB79F0", "1598891820", upt_array_2D) ;
//    cout << endl ;
//    get("A00E7A8538C058366DA15181CC56FD99", "9E12223B51B3D14342F2DBD05EA8B302", "1598908235", upt_array_2D) ;
//    cout << endl ;
//
//    purchased("493CFB4A87C50804C94C0CF76ABD19CD", upt_array_2D) ; // 沒有sale
//    cout << endl ;
//    purchased("A00E7A8538C058366DA15181CC56FD99", upt_array_2D) ;
//    cout << endl ;
//
//    clicked("77FAD5E994EC210B8F7735375528CD30", "0BC06C9B6B6CF82C2624C66C6EEBFE2D", set_pu_array_2D) ;
//    cout << endl ;
//    clicked("2BB964EEE2FB335629C34A7A4E1E9363", "0CFD78123AAF2310B0196C4A6BDB2A3D", set_pu_array_2D) ;
//    cout << endl ;
//
//    profit("1598891820", "0", set_u_array_1D, set_ut_array_2D, set_u1_t_array_2D) ;
//    cout << endl ;
//    profit("1598859587", "0.01", set_u_array_1D, set_ut_array_2D, set_u1_t_array_2D) ;
//    cout << endl ;
//    profit("1598908235", "0.01", set_u_array_1D, set_ut_array_2D, set_u1_t_array_2D) ;
//    cout << endl ;
    
    vector<string> read_lines(0, "0") ;
    int begin = 0 ;
    while(getline(cin,line))
    {
        if (line == "quit")
            break ;
        begin = 0 ;
        for (int i = 0; i <= line.size() - 1; i++)
        {
            if (line.substr(i, 1) == " ") // 此處是以空格分隔而非tab
            {
                read_lines.push_back(line.substr(begin, i - begin)) ;
                begin = i + 1 ;
            }
        }
        read_lines.push_back(line.substr(begin, line.size() - begin)) ; // 補上最後一個元素

        cout << "********************" << endl ;
        if (read_lines[0] == "get")
            get(read_lines[1], read_lines[2], read_lines[3], upt_array_2D) ;
        else if (read_lines[0] == "purchased")
            purchased(read_lines[1], upt_array_2D) ;
        else if (read_lines[0] == "clicked")
            clicked(read_lines[1], read_lines[2], set_pu_array_2D) ;
        else
            profit(read_lines[1], read_lines[2], set_u_array_1D, set_ut_array_2D, set_u1_t_array_2D) ;
        cout << "********************" << endl ;
        read_lines.clear() ; // 清空
    }
    return 0;
}

