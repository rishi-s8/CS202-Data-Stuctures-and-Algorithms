template<class Item>
void Swap(Item& a, Item& b)
{
        Item temp = a;
        a=b;
        b=temp;
}

template<class Item>
LinearList<Item>::LinearList()
{
        MaxSize=0;
        len=0;
        element=NULL;
}

template<class Item>
LinearList<Item>::LinearList(const int& MaxListSize)
{
        MaxSize=MaxListSize;
        len=0;
        element= new Item[MaxListSize];
}

template<class Item>
LinearList<Item>::~LinearList()
{
        MaxSize=0;
        len=0;
        delete element;
}

template<class Item>
Item& LinearList<Item>::operator[](const int& i)
{
        if(i>MaxSize-1)
        {
                cerr << "Overflow." << endl;
                exit(-1);
        }
        else if(i>=len) len=i+1;
        return element[i];
}



template<class Item>
int LinearList<Item>::length()
{
        return len;
}

template<class Item>
int LinearList<Item>::maxSize()
{
        return MaxSize;
}

template<class Item>
Item LinearList<Item>::returnListElement(const int k)
{
        if(k>MaxSize-1)
        {
                cerr << "Overflow." << endl;
                exit(-2);
        }
        else
                return element[k];
}

template<class Item>
bool LinearList<Item>::find(const int k, Item& x)
{
        if(k>MaxSize-1)
                return false;
        x=element[k];
        return true;
}

template<class Item>
int LinearList<Item>::search(Item& x)
{
        for(int i=0; i<len; ++i)
                if(element[i]==x) return i;
        return -1;
}

template<class Item>
void LinearList<Item>::deleteElement(const int k, Item& x)
{
        if(k>MaxSize-1)
        {
                cerr << "Overflow." << endl;
                exit(-3);
        }
        x=element[k];
        for(int i=k; i<len-1; ++i)
                element[i]=element[i+1];
        --len;
        return x;

}

template<class Item>
void LinearList<Item>::insert(const int k, Item& x)
{
        for(int i=len; i>k+1; --i)
                element[i]=element[i-1];
        ++len;
        element[k+1]=x;
}
