//  -fno-elide-constructors

#include <string>

#define $           printf ("-->[%3d]%*s%s\n", __LINE__, Level * 2, "", __PRETTY_FUNCTION__);
#define $DO(stmt)   printf ("\n-->[%3d]%*s%s:\t[%s]\n", __LINE__, Level * 2, "", __PRETTY_FUNCTION__, #stmt); stmt

#define $WHO        printf ("%*s'%s'[%p] = %d\n", Level *2 + 8, "", name_.c_str(), this, number_);

#define $BEGIN      $ indent _indent;


int Level = 0;

struct indent {
    indent() {
        printf ("%*s%s\n", Level * 2 + 8, "", "{");
        Level+=2;
    }
    ~indent() {
        Level-=2;
        printf ("%*s%s\n", Level * 2 + 8, "", "}");
    }
};


struct car {
    int number_;
    std::string name_;

    car ():
        number_ (0),
        name_ ("")
    {
        $BEGIN
        $WHO
    }
    //-------------------------------------------
    car (int init_number, std::string init_name):
        number_ (init_number),
        name_ (init_name)
    {
        $BEGIN
        $WHO
        init_number++;
    }
    //-------------------------------------------
    car (const car& init_car):
        number_ (init_car.number_),
        name_ ("copy of (" + init_car.name_ + ")")
    {
        $BEGIN
        $WHO
    }
    //-------------------------------------------
    car (car&& init_car):
        number_ (std::move (init_car.number_)),                  // std::move not assigns 'int' zero
        name_ ("steal of (" + std::move (init_car.name_) + ")")
    {
        $BEGIN
        $WHO
    }
    //-------------------------------------------
    car& operator = (const car& right)
    {
        $BEGIN
        number_ = right.number_;
        name_ = ("copy of (" + right.name_ + ")");
        $WHO
        return *this;
    }
    //-------------------------------------------
    car& operator = (const car&& right)
    {
        $BEGIN
        number_ = std::move (right.number_);
        name_ = "steal of (" + std::move(right.name_) + ")";
        $WHO
        return *this;
    }

    //-------------------------------------------
    ~car ()
    {
        $BEGIN
        $WHO
    }
};

car operator + (const car& left, const car& right) {
        $BEGIN
        car result (0, "result");
        result.number_ = left.number_ + right.number_;
        result.name_ = result.name_ + " = (" + left.name_ + ") + (" + right.name_ + ")";

        fprintf(stderr, "%*s%s[%p] = %d\n", Level * 2 + 8, "", (result.name_).c_str(), &result, result.number_);

        return result;
    }

int main()
{
    $DO (car car1;)
    $DO (car car2 (44, "MERCEDES");)
    $DO (car car3 (67, "BMW");)


    $DO (car car4 = car3 + car2;)
    $DO (car1 = car4 + car3;)

    printf ("---------END---------);
    return 0;
}
