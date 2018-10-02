//利用队列打印杨辉三角

package PascalTriangle;

public class Queue {
    class node {
        int data;
        node next;
    }

    private node fount;
    private node rear;
    private int length;

    {
        fount = new node();
        rear = new node();
        length = 0;
        fount = rear;
    }

    public void setFount (node fount) {
        this.fount = fount;
    }

    public void setRear (node rear) {
        this.rear = rear;
    }

    public node getFount () {
        return fount;
    }

    public node getRear () {
        return rear;
    }

    public void setLength (int length) {
        this.length = length;
    }

    public int getLength () {
        return length;
    }


    public boolean QueueEmpty () {
        if (fount == rear) {
            return true;
        }
        return false;
    }

    public void EnQueue (int e) {
        rear.data = e;
        rear.next = new node();
        rear = rear.next;
        length++;
    }

    public int DeQueue () {
        if (!QueueEmpty()) {
            int e = fount.data;
            fount = fount.next;
            length--;
            return e;
        }
        System.out.println("没有数据");
        System.exit(0);
        return 0;
    }

    //返回队列长度，不如getLength()好用
    public int QueueLength () {
        int length = 0;
        node foo = fount;
        while (foo.next != null) {
            ++length;
            foo = foo.next;
        }
        return length;
    }

    public static void main (String[] args) {
        Queue Triangle = new Queue();
        Triangle.EnQueue(1);
        Triangle.EnQueue(2);
        Triangle.EnQueue(1);
        int a, b, i = 0;
        while (i < 11) {
            a = Triangle.getFount().data;
            b = Triangle.getFount().next.data;
            System.out.print(Triangle.DeQueue() + " ");
            if (a == 1) {
                Triangle.EnQueue(1);
                if (b == 1) {
                    System.out.println();
                    ++i;
                } else
                    Triangle.EnQueue(a + b);
            } else {
                Triangle.EnQueue(a + b);
            }
        }
    }
}
