#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct st{
    int roll_no;
    char name[40];
    float mark;
    struct st* nxt;
} ST;
typedef struct bf{
    int t_r;
    struct bf *nxt;
} BF;

void choice_menu_dp(void);
void delete_menu_dp(void);
void modify_menu_dp(void);
void output_dp(void);
void save_menu_dp(void);
void sort_menu_dp(void);
void add_end(ST **,int *,BF **,int *);
void delete_node(ST **,BF **);
void delete_roll(ST **,BF **);
void delete_name(ST **,BF **);
void deletion_bf(BF **,int);
void delete_all(ST**);
void save(ST **);
void save_exit(ST **);
void exit_ws(void);
void modify(ST **);
void modify_roll(ST **);
void modify_name(ST **);
void modify_mark(ST **);
void print(ST **);
void reverse(ST **);
void print_repeated(ST ***,int );
int count_repeat_nm(ST **P, char *);
int count_repeat_mk(ST **P, float );
void sort(ST **);
void sort_name(ST **);
void sort_mark(ST **);
void add_new(ST **,int *,BF **,int *);

int main()
{
    ST *hptr = NULL;
    BF *b_hp = NULL;
    int roll = 0;
    int temp = 0;
    char op;
    while(1)
    {
    system("clear");
    choice_menu_dp();
    scanf(" %c",&op);
    switch(op)
    {
        case 'a':
        case 'A':   add_new(&hptr,&roll,&b_hp,&temp);   
                    break;
                    
        case 'd':
        case 'D':   delete_node(&hptr,&b_hp);
                    break;
                    
        case 'm':
        case 'M':   modify(&hptr);
                    break;
        
        case 'v':
        case 'V':   save(&hptr);
                    break;
                    
        case 's':
        case 'S':   print(&hptr);
                    break;
                    
        case 'e':
        case 'E':   save(&hptr);
                    break;
                    
        case 't':
        case 'T':   sort(&hptr);
                    break;
                    
        case 'l':
        case 'L':   delete_all(&hptr);
                    break;
                    
        case 'r':
        case 'R':   reverse(&hptr);
                    break;
                    
        default : puts("Invalid option....");
    }
    
    }
}

void add_new(ST **hptr,int *roll,BF **b_hp,int *temp)
{
    char opt;
    do{
        add_end(hptr ,roll ,b_hp ,temp);
        puts("Want to add onr more data....(y/n)");
        scanf(" %c",&opt);
    }while(opt == 'y');
}


void add_end(ST **ptr,int *r,BF **hp,int *t)
{
    int r_n = *r;   //roll_no is initialized with the main func. variable
    int t_n = *t;   //temp_no(for comaprison on the purpose of deletion) is initialized
    ST *p = *ptr;
    BF *bf = *hp;
    ST *temp = (ST *)malloc(sizeof(ST));
    puts("Enter the student record...in the format of (name - mark_obtained)");
    scanf("%s%f",temp->name,&temp->mark);
//++r_n;  // as the roll number to be increased... by itself
    if(*hp == NULL){
        ++r_n;
        temp->roll_no = r_n;
        t_n = r_n;
    }
    else{
	int TEMP = bf->t_r;	// declaring a temp variable for deletion of that number.. once it is assigned
	temp->roll_no = TEMP;
	deletion_bf(&bf,TEMP);
    }
   /* temp->roll_no = r_n;
    t_n = r_n; */
    temp->nxt = NULL;
    if(*ptr == NULL) *ptr = temp;
    else{
        ST *last = p;
        while(last->nxt)    last = last->nxt;
        last->nxt = temp;
    }
    *r = r_n;   //to update the roll_no in the main func.
    *t = t_n;   //to update the temp_no in the maain func.
    *hp = bf;	//to update the buffer value in the main function...
}

void add_bfend(BF **ptr,int tp)
{
    BF *p = *ptr;
    BF *temp = (BF *)malloc(sizeof(BF));
    temp->t_r = tp;
    if(*ptr == NULL){
        *ptr = temp;
        temp->nxt = NULL;
    }
    else{
        BF *last = *ptr;
        while(last->nxt)
            last = last->nxt;
        last->nxt = temp;
    }
    
}

void print(ST** ptr)
{
    char c;
    ST* p = *ptr;
    output_dp(); // Add this
    while(p)
    {
        printf("| %-7d | %-27s | %6.2f |\n",p->roll_no,p->name,p->mark);
        p = p->nxt;
    }
    puts("|_________|_____________________________|________|");
    printf("Want to exit from displaying(y/n):");
    scanf(" %c",&c);
}


void reverse(ST **ptr)
{
    int i = 0, j, k, c = 0;
    ST *p = *ptr;
    ST *cptr = *ptr;
    ST *t = (ST *)malloc(sizeof(ST));
    int size = sizeof(ST) - sizeof(ST *); 
    while (p)
    {
        c++;
        p = p->nxt;
    }
    ST **temp = (ST **)malloc(c * sizeof(ST *));
    while (i < c && cptr)
    {
        temp[i++] = cptr;
        cptr = cptr->nxt;
    }
    // Swap contents of nodes (excluding pointers)
    for (j = 0, k = c - 1; j < k; j++, k--)
    {
        memcpy(t, temp[j], size);
        memcpy(temp[j], temp[k], size);
        memcpy(temp[k], t, size);
    }
}


void sort(ST **ptr) //&hptr
{
        ST *p = *ptr;
        sort_menu_dp();
        char opt;
        puts("Enter the mode of option for sorting... ");
        scanf(" %c",&opt);
        switch(opt)
        {
                case 'n':
                case 'N':       sort_name(&p);
                                break;
                case 'p':
                case 'P':       sort_mark(&p);
                                break;
                default:        puts("Invalid option....");
        }
}

void sort_name(ST **ptr)
{
    ST *p = *ptr;
    ST *q = NULL;
    int i=0;
    char bf[40];
    float mk_bf=0;
    while(p)
    {
        q = p->nxt;
        while(q)
        {
            i = strcmp(p->name,q->name);
            if(i>0){
                strcpy(bf,q->name);
                mk_bf = q->mark;
                strcpy(q->name,p->name);
                q->mark = p->mark;
                strcpy(p->name,bf);
                p->mark = mk_bf;
            }
            q = q->nxt;
        }
        p = p->nxt;
    }
}

void sort_mark(ST **ptr)
{
    ST *p = *ptr;
    ST *q = NULL;
    int i=0;
    char bf[40];
    float mk_bf=0;
    while(p)
    {
        q = p->nxt;
        while(q)
        {
            if(p->mark > q->mark){
                strcpy(bf,q->name);
                mk_bf = q->mark;
                strcpy(q->name,p->name);
                q->mark = p->mark;
                strcpy(p->name,bf);
                p->mark = mk_bf;
            }
            q = q->nxt;
        }
        p = p->nxt;
    }
}

void delete_all(ST** ptr)
{
    ST* p = *ptr;
    ST* t;
    while(p)
    {
        t = p->nxt;
        free(p);
        p = t;
    }
    *ptr = NULL;
}

void delete_node(ST **ptr, BF **hp)
{
    
    char opt;
    delete_menu_dp();
    puts("Enter the choice to delete the particular node....");
    scanf(" %c",&opt);
    switch(opt){
        case 'r':
        case 'R': delete_roll(ptr,hp);
                        break;

        case 'n':
        case 'N': delete_name(ptr,hp);
                        break;

        default : puts("Invalid input....");
                  break;
    }
}

void delete_roll(ST **p,BF **bhp)   // **p & **bhp holds the address of the head pointer of both structures....
{
    ST *ptr = *p;
    BF *bh = *bhp;
    ST *t;
    ST *last = NULL;  // Initially no previous node
    int r;  // declare a variable for the roll_no
    int TEMP;  // variable for passing in the buffer to store the deleted data...

    puts("Enter the roll number to delete the student data.....");
    scanf("%d", &r);
    while(ptr)
    {
        t = ptr->nxt;
        if((ptr->roll_no == r) && (ptr == *p))
        {
            TEMP = ptr->roll_no;
            add_bfend(&bh,TEMP);
            free(ptr);
            *p = t;
        }
                else if(ptr->roll_no == r)
        {
            TEMP = ptr->roll_no;
            add_bfend(&bh,TEMP);
            last->nxt = t;
            free(ptr);
        }
        else
            last = ptr;  // Only update 'last' if no deletion
        ptr = t;
    }
        *bhp = bh;
}

void delete_name(ST **p,BF **bhp)
{
    ST *ptr = *p;       //assining of std struct
    BF *bh = *bhp;      //assining of buffer struct
    ST *t;      //declaring a temporary variable to hold the addr.
    ST *last = NULL;  // Initially no previous node
    char nm[40];
    int TEMP;  // variable for passing in the buffer to store the deleted data...
    puts("Enter the name to delete the student data.....");
    scanf("%s", nm);
    //int c = count_repeat_nm(p, nm);
    //
    //
    //need a driver for the purpose of the deletion of the repewated elements in the name of the record....,    try to refer the modify search definition ....;
    //
    //
    //
    //
    while(ptr)
    {
        t = ptr->nxt;
        if((strcmp(ptr->name, nm) == 0) && (ptr == *p))
        {
            TEMP = ptr->roll_no;
            add_bfend(&bh,TEMP);
            free(ptr);
            *p = t;
        }
        else if(strcmp(ptr->name, nm) == 0)
        {
            TEMP = ptr->roll_no;
            add_bfend(&bh,TEMP);
            last->nxt = t;
            free(ptr);
        }
        else
            last = ptr;  // Only update 'last' if no deletion
        ptr = t;
    }
    *bhp = bh;
}

void deletion_bf(BF **bp,int t_num)
{
        BF *p = *bp;
        BF *t;
        BF *last ;
        while(p)
        {
                t = p->nxt;
                if((p->t_r == t_num)&&(p == *bp))
                {
                        *bp = t;
                        free(p);
                }
                else if(p->t_r == t_num)
                {
                        last->nxt = t;
                        free(p);
                }
                p = t;
                last = p;
        }
}

void save(ST **ptr)
{
      //  ST *p = *ptr;
        save_menu_dp();
        char opt;
        puts("Enter the option...");
        scanf(" %c",&opt);
        switch(opt)
        {
                case 's':
                case 'S': save_exit(ptr);
                          break;
                case 'e':
                case 'E': exit_ws();
                          break;

                default : puts("Invalid option....");
        }
}

void save_exit(ST **ptr)
{
        ST *p = *ptr;
        //FILE *fp = fopen("data.dat","w");	// to display only the new data...
        FILE *fp = fopen("data.dat","a+");	// to display the existing content...
        while(p){
                fprintf(fp,"%d %s %f\n",p->roll_no,p->name,p->mark);
                p = p->nxt;
        }
	fclose(fp);
	exit(0);	//on successful command
}
void exit_ws(void)
{
        FILE *fp = fopen("data.dat","a+");
        fclose(fp);
	exit(0);	//on successful command
}

void modify(ST **ptr)
{
        modify_menu_dp();
        char opt;
        puts("Enter the option to modify....");
        scanf(" %c",&opt);
        switch(opt)
        {
                case 'r':
                case 'R':       modify_roll(ptr);
                                break;
                case 'n':
                case 'N':       modify_name(ptr);
                                break;
                case 'p':
                case 'P':       modify_mark(ptr);
                                break;
                default : puts("Invalid option.....");
        }
}

void modify_roll(ST **ptr)
{
        ST *p = *ptr;
        int i;
        puts("Enter the roll nnumber to modify the student data....");
        scanf("%d",&i);
        while(p){
                if(p->roll_no == i){
                        puts("Enter the new data to modify the old data....");
                        scanf("%s%f",p->name,&p->mark);
						//break;
                }
                p = p->nxt;
        }
}

void modify_name(ST **ptr)
{
    ST *p = *ptr;
    char bf[40];
    int c = 0, i = 0;
    puts("Enter the name to search for modification....");
    scanf("%s", bf);
    c = count_repeat_nm(ptr, bf);
    //printf("%d\n", c);
    ST **temp = (ST **)malloc(c * sizeof(ST *));
    ST *curr = *ptr;
    i = 0;
    while (curr && i < c)
    {
        if (strcmp(curr->name, bf) == 0)
        {
            temp[i++] = curr;
        }
        curr = curr->nxt;
    }
    if (c == 1)
    {
        puts("Enter new name and marks:");
        scanf("%s %f", temp[0]->name, &temp[0]->mark);
		//break;
    }
    else
        print_repeated(&temp, c);
}

void modify_mark(ST **ptr)
{
    ST *p = *ptr;
    float bf_m;
    int c = 0, i = 0;
    puts("Enter the mark to search for modification....");
    scanf("%f",&bf_m);
    c = count_repeat_mk(ptr, bf_m);
    //printf("%d\n", c);
    ST **temp = (ST **)malloc(c * sizeof(ST *));
    ST *curr = *ptr;
    i = 0;
    while (curr && i < c)
    {
            if (curr->mark == bf_m)
        {
            temp[i++] = curr;
        }
        curr = curr->nxt;
    }
    if (c == 1)
    {
        puts("Enter new name and marks:");
        scanf("%s %f", temp[0]->name, &temp[0]->mark);
		//break;
    }
    else
        print_repeated(&temp, c);
}

int count_repeat_nm(ST **P, char *p)
{
    ST *ptr = *P;
    int c = 0;
    while(ptr)
    {
        if(strcmp(ptr->name, p) == 0)
            c++;
        ptr = ptr->nxt;
    }
    return c;
}

int count_repeat_mk(ST **P, float p)
{
    ST *ptr = *P;
    int c = 0;
    while(ptr)
    {
        if(ptr->mark == p)
            c++;
        ptr = ptr->nxt;
    }
    return c;
}

void print_repeated(ST ***temp,int c)
{
        ST **t = *temp;
		puts("Displaying the repeated elements.....");
		output_dp();
        for(int i=0;i<c;i++)
        printf("| %-7d | %-27s | %6.2f |\n",t[i]->roll_no,t[i]->name,t[i]->mark);
		puts("|_________|_____________________________|________|");
        puts("calling the modify_roll()...");
        modify_roll(*temp);
}

void choice_menu_dp(void)
{
    printf(" _________________________________\n");//int32_t
    printf("|                                 |\n");
    printf("| ***** STUDENT RECORD MENU ***** |\n");
    printf("|_________________________________|\n");//int32_t
    printf("|                                 |\n");
    printf("| a/A  : add new record           |\n");
    printf("| d/D  : delete a record          |\n");
    printf("| s/S  : show the list            |\n");
    printf("| m/M  : modify a record          |\n");
    printf("| v/V  : save                     |\n");
    printf("| e/E  : exit                     |\n");
    printf("| t/T  : sort the list            |\n");
    printf("| l/L  : delete all the records   |\n");
    printf("| r/R  : reverse the list         |\n");
    printf("|                                 |\n");
    printf("| Enter your choice :             |\n");
    printf("|_________________________________|\n");//int32_t
}

void delete_menu_dp(void)
{
    printf(" _________________________________\n");//int32_t
    printf("|                                 |\n");
    printf("| r/R  : enter roll.no to delete  |\n");
    printf("| n/N  : enter name to delete     |\n");
    printf("|                                 |\n");
    printf("|                                 |\n");
    printf("|                                 |\n");
    printf("|                                 |\n");
    printf("|                                 |\n");
    printf("|                                 |\n");
    printf("|_________________________________|\n");//int32_t
}

void save_menu_dp(void)
{
    printf(" _________________________________\n");//int32_t
    printf("|                                 |\n");
    printf("| Enter                           |\n");
    printf("| s/S  : save and exit            |\n");
    printf("| e/E  : exit without saving      |\n");
    printf("|                                 |\n");
    printf("|                                 |\n");
    printf("|                                 |\n");
    printf("|                                 |\n");
    printf("|                                 |\n");
    printf("|_________________________________|\n");//int32_t
}

void sort_menu_dp(void)
{
    printf(" _________________________________\n");//int32_t
    printf("|                                 |\n");
    printf("| Enter                           |\n");
    printf("| n/N  : sort with name           |\n");
    printf("| p/P  : sort with percentage     |\n");
    printf("|                                 |\n");
    printf("|                                 |\n");
    printf("|                                 |\n");
    printf("|                                 |\n");
    printf("|                                 |\n");
    printf("|_________________________________|\n");//int32_t
}

void modify_menu_dp(void)
{
    printf(" _______________________________________________\n");//int32_t
    printf("|                                               |\n");
    printf("| Enter which record to search for modification |\n");
    printf("| r/R  : to search a roll.no                    |\n");
    printf("| n/N  : to search a name                       |\n");
    printf("| p/P  : percentage based                       |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("|_______________________________________________|\n");//int32_t
}

void output_dp(void)
{
    puts(" ________________________________________________");
    puts("|         |                             |        |");//8,29,8
    puts("| roll_no | name \t\t\t| mark   |");
    puts("|_________|_____________________________|________|");
}
