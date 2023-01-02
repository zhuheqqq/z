# include <iostream>
using namespace std;

class Rectangle
{
    private:
    double width;//宽
    double height;//高
    
    public:   
    Rectangle(double width = 1.0, double height = 1.0)
    {
        this->width = width;
        this->height = height;
    }
    
    double getWidth(void)
    {
        return width;
    }
    
    void setWidth(double width)
    {
        this->width = width;
    }
    
    double getHeight(void)
    {
        return height;
    }
    
    void setHeight(double height)
    {
        this->height = height;
    }
    
    double getArea(void)
    {
        return width*height;
    }
    
    double getPerimeter(void)
    {
        return (width+height)*2;
    }
};

int main(void)
{
    Rectangle x;
    //cout<<"测试："<<endl;
    cout<<"宽度："<<x.getWidth()<<endl;
    cout<<"高度："<<x.getHeight()<<endl;
    cout<<"面积："<<x.getArea()<<endl;
    cout<<"周长："<<x.getPerimeter()<<endl<<endl;

    double width;
    double height;
    cout<<"输入宽：" ;
    cin>>width;
    cout<<"输入高：" ;
    cin>>height;
    Rectangle y(width, height);
    cout<<"宽度："<<y.getWidth()<<endl;
    cout<<"高度："<<y.getHeight()<<endl;
    cout<<"面积："<<y.getArea()<<endl;
    cout<<"周长："<<y.getPerimeter()<<endl;
    return 0;
    
}