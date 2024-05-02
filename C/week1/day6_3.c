#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5


int num_in_rank[NUM_RANKS];
int num_in_suit[NUM_SUITS];
bool straight, flush, four, three;   
int pairs;  // 对子数只能为0、1、2


void read_cards(void);
void analyze_hand(void);
void print_result(void);

int main(void)
{
    for ( ; ; ) {
        read_cards();
        analyze_hand();
        print_result();
    }
}

void read_cards(void)
{
    char ch, rank_ch, suit_ch;
    int rank, suit;
    
    bool bad_card, duplicate_card;      //输入错误时和输入重复时的标志
    int cards_read = 0;

    //初始化
    for (rank = 0; rank < NUM_RANKS; rank++) {
        num_in_rank[rank] = 0;
    }
    for (suit = 0; suit < NUM_SUITS; suit++) {
        num_in_suit[suit] = 0;
    }

    while (cards_read < NUM_CARDS) {
        bad_card = false;

        printf("Enter a card: ");

        rank_ch = getchar();
        suit_ch = getchar();

        //判断从第二次开始的输入有没有错误
        while ((ch = getchar()) != '\n')
            if (ch != ' ')
                bad_card = true;


        if (rank_ch == '0')
            exit(EXIT_SUCCESS);

        switch(rank_ch) {
            case '2': rank = 0; break;
            case '3': rank = 1; break;
            case '4': rank = 2; break;
            case '5': rank = 3; break;
            case '6': rank = 4; break;
            case '7': rank = 5; break;
            case '8': rank = 6; break;
            case '9': rank = 7; break;
            case 't': case 'T': rank = 8; break;
            case 'j': case 'J': rank = 9; break;
            case 'q': case 'Q': rank = 10; break;
            case 'k': case 'K': rank = 11; break;
            case 'a': case 'A': rank = 12; break;
            default: bad_card = true;
        }

        switch(suit_ch) {
            case 'c': case 'C': suit = 0; break;
            case 'd': case 'D': suit = 1; break;
            case 'h': case 'H': suit = 2; break;
            case 's': case 'S': suit = 3; break;
            default: bad_card = true;
        }

        if (bad_card)
            printf("Bad card; ignored.\n");
        else if (num_in_rank[rank] > 0 && num_in_suit[suit] > 0)
            printf("Duplicate card; ignored.\n");
        else {
            num_in_rank[rank]++;
            num_in_suit[suit]++;
            cards_read++;
        }
    }
}

void analyze_hand(void)
{
    int num_consec = 0;
    int rank, suit;
    
    straight = false;
    flush = false;
    four = false;
    three = false;
    pairs = 0;

    // 检查同花
    for (suit = 0; suit < NUM_SUITS; suit++)
        if (num_in_suit[suit] == NUM_CARDS)
            flush = true;

    // 检查顺子
    rank = 0;
    while (num_in_rank[rank] == 0)
        rank++;
    for( ; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)
        num_consec++;
    if (num_consec == NUM_CARDS) {
        straight = true;
        return;     //检查完有同花或者顺子后可以直接返回
    }

    // 检查四条、三条、三条+一对、对子
    for (rank = 0; rank < NUM_RANKS; rank++) {
        if (num_in_rank[rank] == 4)
            four = true;
        if (num_in_rank[rank] == 3)
            three = true;
        if (num_in_rank[rank] == 2)
            pairs++;
    }
}

void print_result(void)
{
    if (straight && flush)
        printf("同花顺");
    else if (four)         
        printf("四条");
    else if (three && pairs == 1)   
        printf("葫芦");
    else if (flush)        
        printf("同花");
    else if (straight)    
        printf("顺子");
    else if (three)        
        printf("三条");
    else if (pairs == 2)   
        printf("两对");
    else if (pairs == 1)   
        printf("一对");
    else                   
        printf("高牌");
    printf("\n\n");
}