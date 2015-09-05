/* binsearch 寻找key下标，不存在 return -1 */
 
/* binsearch 注意点【找不到 vs 死循环】
 * 1. left <= right 如改为 left < right 可能找不到key
 *    例如 1 2 3 4 5；key=5; left==right时候才搜到key
 * 2. left = mid + 1;
 *    如上left改为=mid，可能死循环，例如上面例子，
 *    当left指向4时候，right指向5，此时，死循环；
 *    死循环的根本原因在于left，当两个指针left与right相邻
 *    left可能永远等于mid，而right不会因为等于mid死循环
 */
int binsearch(int * arr, int lef, int rig, int key)
{
    if(!arr)    
        return -1;
    int left = lef, right = rig;
    while(left <= right)
    {
        int mid = left + ((right-left)>>1);
        if(arr[mid] < key)
        {
            left = mid + 1;
        }else if(arr[mid] > key)
        {
            right = mid - 1;
        }else
            return mid;
    }
    return -1;
}
 
/* binsearch_min 返回key(可能有重复)第一次出现的下标，如无return -1
 *
 * binsearch_min 注意点【死循环】
 * 1. 如果while(left < right)改为(left <= right)可能死循环；
 * 2. 循环结束条件，left == right
 *
 * 该代码我测试了很多用例，没发现反例，我认为是对的
 * 但网上都是用的left<right-1的条件并分别对arr[left]和arr[right]
 * 进行检查；我认为我写的更简练，希望有兴趣的读者帮忙review这段代码
 * 如发现反例指出错误，感激不尽，嘿
 */
int binsearch_min(int * arr, int lef, int rig, int key)
{
    if(!arr)
        return -1;
    int left = lef, right = rig;
    while(left < right)
    {
        int mid = left + ((right-left)>>1);
        if(arr[mid] < key)
        {
            left = mid+1;
        }else
        {
            right = mid;
        }
    }
    if(arr[left] == key)    return left;
    return -1;
}
 
/* binsearch_max 返回key(可能有重复)最后一次出现的下标，如无return -1
 *
 * binsearch_max 注意点【死循环 vs 越过目标位置】
 * 1. 如果改为while(left < right)可能死循环；
 * 2. 如果left=mid改为left=mid+1；则有可能越过目标位置
 * 3. 循环结束条件，left == right || left == right -1
 *
 * 如非要死记：找最大的等号放<=key的位置，找最小的等号放>=key位置
 */
int binsearch_max(int * arr, int lef, int rig, int key)
{
    if(!arr)    return -1;
    int left = lef, right = rig;
    while(left < right -1)
    {
        int mid = left + ((right-left)>>1);
        if(arr[mid] <= key)
        {
            left = mid;
        }else
        {
            right = mid;
        }
    }
    if(arr[right] == key) // 找max，先判断right
    {
        return right;
    }else if(arr[left] == key)
    {
        return left;
    }else
        return -1;
}
 
/* binsearch_justsmall 返回刚好小于key的元素下标，如无return -1
 *
 * binsearch_justsmall 注意点【死循环 vs 越过目标位置】
 * 1. 如果改为while(left < right)可能死循环；因为left=mid的缘故
 * 2. 如果left=mid改为left=mid+1；则有可能越过目标位置
 * 3. 循环结束条件，left == right || left == right -1
 */
int binsearch_justsmall(int * arr, int lef, int rig, int key)
{
    if(!arr)    return -1;
    int left = lef, right = rig;
    while(left < right - 1)
    {
        int mid = left + ((right-left)>>1);
        if(arr[mid] < key)
        {
            left = mid;
        }else
        {
            right = mid - 1;
        }
    }
    if(arr[right] < key) // 找刚好小于，先判断right
    {
        return right;
    }else if(arr[left] < key)
    {
        return left;
    }else
        return -1;
}
 
/* binsearch_justgreat 返回刚好大于key的元素下标，如无return -1
 *
 * binsearch_justgreat 注意点【死循环 vs 检查元素是否大于key】
 * 1. 如果改为while(left <= right)可能死循环；因为right = mid；
 * 2. 最后注意检查arr[right]是否大于key
 * 3. 循环结束条件，left == right
 */
int binsearch_justgreat(int * arr, int lef, int rig, int key)
{
    if(!arr)    return -1;
    int left = lef, right = rig;
    while(left < right)
    {
        int mid = left + ((right-left)>>1);
        if(arr[mid] <= key)
        {
            left = mid + 1;
        }else
        {
            right = mid;
        }
    }
    if(arr[right] > key) return right;
    return -1;
}

#define N 20  // 测试数组大小
 
void outputarr(int * arr, int len)
{
    for(int i = 0; i < len; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}
 
void main()
{
    int testcase = 0;
    scanf("%d", &testcase);
    int * arr = new int [N];
 
    srand(1); // 设置随机种子
 
    while(testcase--)
    {
        for(int i = 0; i < N; ++i)  // 随机生成数组
        {
            arr[i] = rand() % (N);
        }
        int key = rand() % (N);
        outputarr(arr,N);
        std::sort(arr,arr+N);      // 排序
        outputarr(arr,N);
 
        printf("binsearch:           key-%d %d\n", key, binsearch(arr,0,N-1,key));
        printf("binsearch_min:       key-%d %d\n", key, binsearch_min(arr,0,N-1,key));
        printf("binsearch_max:       key-%d %d\n", key, binsearch_max(arr,0,N-1,key));
        printf("binsearch_justsmall: key-%d %d\n", key, binsearch_justsmall(arr,0,N-1,key));
        printf("binsearch_justgreat: key-%d %d\n", key, binsearch_justgreat(arr,0,N-1,key));
    }
 
    delete [] arr;
}
