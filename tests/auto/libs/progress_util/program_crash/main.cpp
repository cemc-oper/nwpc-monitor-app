struct Foo{
    int i;
};

int main(int argc, char *argv[])
{
    Foo *f = new Foo;
    return f->i;
}
