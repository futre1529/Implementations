/*
 3-1 DW BOXPLOT PROBLEM*/
import java.awt.Color;
import java.awt.Frame;
import java.awt.Graphics;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
public class boxplot extends Frame{
public static void sort(int[] a,int k)
{
    for(int i=0;i<k+1 && a[i]>0;i++)
    {
        int j;
        int key=a[i];
        for(j=i-1;j>=0 && a[j]>key;j--)
        { a[j+1]=a[j];}
        a[j+1]=key;
    }
}
static int m1[],m2[],min[],max[],m3[];// q1,q2,q3;
public boxplot(Color ballcolor) {
    super();        
    setSize(600,600);
            setTitle("Boxplot");
            setVisible(true);
      
            repaint();
            this.setBackground(Color.RED);
        }
        Graphics C;
public static void main(String args[]) throws IOException
{
    m1=new int[5];
     m2=new int[5];
      m3=new int[5];
       min=new int[5];
        max=new int[5];
        
     boxplot b=new boxplot(Color.blue);
        b.show();
    BufferedReader br = null;
       try{ 
            br=new BufferedReader(new FileReader("GG.txt"));
        } 
    catch(FileNotFoundException ex)
    {
    }
     String  line=null;
     try{
    line=br.readLine();
     }
     catch(NullPointerException e){}
    while((line)!=null)
    {
        double q1,q2,q3;
        int fromindex=0,space1=0,space;
        int a[]=new int[15];
        int i=0;
        int l=line.length();
        int coma=line.indexOf(',', fromindex);
        System.out.println(coma);
        while(true)
        {
             space=line.indexOf(' ',fromindex);
            String s=line.substring(fromindex,space);
            fromindex=space+1;
            a[i++]=Integer.parseInt(s);
            if(fromindex==coma)
            { break;}
        }
        int k=i;
          for(int i1=0;i1<=k;i1++)
        {
            System.out.println(a[i1]);
        }
        sort(a,k);
         System.out.println("start");
        for(int i1=0;i1<k;i1++)
        {
            System.out.println(a[i1]);
        }
         System.out.println("over");
        int c=k;
        if(k%2==0)
        {
            q2=a[k/2]+a[(k/2)-1];
            q2/=2.0;
            k=k/2;
            if(k%2==0)
        {
            q1=a[k/2]+a[(k/2)-1];
            q1/=2.0;
            q3=a[k/2+k]+a[(k/2)+k-1];
            q3/=2.0;
        }
            else
            {
                q1=a[k/2];
                q3=a[k/2+k];
            }
         }
        else
        {
             System.out.println("odd");
            q2=a[k/2];
            k=k/2;
         if(k%2!=0)
         {
            q1=a[k/2];
            q3=a[k/2+k+1];
        }
         else
         {
              System.out.println("again odd");
             q1=a[k/2]+a[(k/2)-1];
            q1/=2.0;
            q3=a[k/2+k]+a[(k/2)+k+1];
            q3/=2.0;
             System.out.println(q1);
              System.out.println(q3);
        }}
        m1[x]=(int)q1;
        m2[x]=(int)q2;
        m3[x]=(int)q3;
        min[x]=a[0];
        max[x]=a[c-1];
         System.out.println(min);
         System.out.println(m1);
         System.out.println(m2);
          System.out.println(m3);
           System.out.println(max);
        try{
    line=br.readLine();
    x++;
     }
     catch(NullPointerException e){}
        b.repaint();
    }
    
}
static int x=0;

        public void paint(Graphics g)
        {  
            g.setColor(Color.blue);
            g.setColor(Color.blue);
        
            for(int i=0;i<10;i++)
            {
                g.drawString(Integer.toString(200-20*i), 20, 30+i*20);
                g.drawLine(45,30+ i*20,50, 30+20*i);
            }
            g.drawLine(50, 10,50,210);
            g.drawLine(50,210,260,210);
            for(int i=0;i<4;i++)
            {
                g.drawString("branch"+Integer.toString(i+1),50+i*50,230);
            }
        
              System.out.println(m3+"Kl");

              for(int i=0;i<x;i++)
              {g.drawRect(60+i*50,230-m3[i],30,m3[i]-m1[i]);
            g.drawLine(60+i*50,230-m2[i], 60+i*50+30,230-m2[i]);
            g.drawLine(60+i*50+15, 230-min[i],60+i*50+15, 230-m1[i]);
            g.drawLine(60+i*50+15,230-m3[i],60+i*50+15,230-max[i]);
              }
     }

    private void FileNotFoundException() {
        throw new UnsupportedOperationException("Not yet implemented");
    }

   
}