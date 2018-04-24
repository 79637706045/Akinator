#include <iostream>
#include <time.h>
#include <cstdlib>
#include <GL/glut.h>

#include<stdio.h>
#include<stdlib.h>
#include <locale.h>
#include<windows.h>
#include<math.h>
#include<conio.h>

#include <vector>
#include <cmath>

/*
����� ������� �������� �� ������������ �����
����� ��� ���������� �� ���, ���, ����


� ����������� �� �������� ��������, ����� � ��� ������� �������
� ���� ����� � ������ ���������� �������� �������?
���� ����� � ������� ������� ����������� ���������
� ��� ������ �� ���������������� ���� ��� �������, ���� ��������� �������� ����� ���������
�������� ��� � ������� , ��� ��������*/

//������� ������� -- ���� ��������

/*���� � ������ ������� ������ ��� ���
�� ����� �� ������ ������������ �����*/
/*
�������� , -- ��� ���� ������ ����� ����, �������� �������� ���� ������ ������ �������*/

//���� �� �������������� � ����� ����� ���� ������ � ����������� �����

/**********************************************/
//�������� ���������, �������� ��������� ����� ��������
typedef struct molekyla{
	// ����������
	double y; // [�] 10^-9, �� ���� ��������� ����� ����� �������� �� ��� ��������
	double x; // [�] 10^-9, �� ���� ��������� ����� ����� �������� �� ��� ��������

	//��������, � ������ ��������
	double vx; //[�/�]
	double vy; //[�/�]

	//����� ��������
	double m; //kg*10^-26

	// ����������� � ��������� ������ ����� ������ ������� mv^2/2 = i/2*k*T => T = ...



} molekyla;
/********************************************/
//��� � ������� ������ �� ��������, �� ������� ���������� ����������
int ys, xs, n_l, n_r;
double T_l, T_r, i = 3, m_l, m_r, d;
molekyla* arr;




void display();

void sbor_info();

void getting_ready();

/*����� ������ � ���� ��������*/
int randpoz(int minim, int maxim);//������� ��������� ����� ���� int �� ��������� ���������, �� ������ ����� min > 0


int peresek(double xp, double yp, double x11, double x12, double x21, double x22, double y11, double y12, double y21, double y22){
	int flag = 0;
	//x1.1 -- ������ ����� �� � ���� ������ ������, �� ����� �����
	double x1max = 0, x1min = 0, x2max = 0, x2min = 0, y1max = 0, y1min = 0, y2max = 0, y2min = 0;
	if(x11 < x12){
		x1min = x11; x1max = x12;
	}
    else{
		x1min = x12; x1max = x11;
	}

	if(x21 < x22){
		x2min = x21; x1max = x22;
	}
	else{
		x2min = x22; x1max = x21;
	}
	////////////////////////////////////////
	if(y11 < y12){
		y1min = y11; y1max = y12;
	}
	else{
		y1min = y12; y1max = y11;
	}

	if(x21 < x22){
		y2min = y21; y1max = y22;
	}
	else{
		y2min = y22; y1max = y21;
	}
	/////////////////////////////////////////

	/*���� � ��� ���� ��� ����� ������ 1 � 2 � �������� ��� � ����, �������� ������ �������� �� � ���������*/
	 if( (xp >= x1min) && (xp <= x1max) && (xp >= x2min) && (xp <= x2max) && (yp >= y1min) && (yp <= y1max) && (yp >= y2min) && (yp <= y2max) ){
	 	flag++;
	 }

	return flag;
}

void move(molekyla* ch, double tay){
	ch->x += tay*ch->vx; ch->y += tay * ch->vy;
}

void ydar_molekyl(double xp, double yp, molekyla* ch1, molekyla* ch2, double* t_pr){//������, ��� ����������� ����� ����� �����?, ��� ������� ������
	double tay = abs((abs(ch1->x - xp)) / (ch1->vx));//�� ������ ��������� ����� ����� ����� �� ������, �������� ��� �� ��������, ����, ����� �����
	*t_pr = tay;/*���������� � ������� ������ ���� �� ����

	//������ ������ ������ � ������� ������ �������, �� ����� ����������, �� ��� ��� �������� ������� ����� ������������ �� ������ ������
	//��� ������ ����� ����� �� ������� �������, ����� ������������ ? ������ ���� ������
	//��������� � ������� ������ ����
	double vcm = ( (ch1->m)*(sqrt((ch1->vx)*(ch1->vx) + (ch1->vy)*(ch1->vy))) + (ch2->m)*(sqrt((ch2->vx)*(ch2->vx) + (ch2->vy)*(ch2->vy))) ) / (ch1->m + ch2->m);
	double vcmx = ( (ch1->m)*(ch1->vx) + (ch2->m)*(ch2->vx)  ) / (ch1->m + ch2->m);
	double vcmy = ( (ch1->m)*(ch1->vy) + (ch2->m)*(ch2->vy)  ) / (ch1->m + ch2->m);
	/* ����� �������� ��������� V_{��������} = V_{��} + V_{��� ��}*/
	/*�������� ����� ����� ����� ��������� ���������� h*/
	/* �� ���� ���������� � ������� ������ ����
	//��������� �������� � ����� ����
	double v1xcm = ch1->vx - vcmx;
	double v1ycm = ch1->vy - vcmy;
	double v2xcm = ch2->vx - vcmx;
	double v2ycm = ch2->vy - vcmy;
	// �������� ���������� ��� ��������, ������� �� ����� ��������, ������ ����� �� ������ ������� �� �� ���������
	double v1xcmh = 0, v1ycmh = 0, v2xcmh = 0, v2ycmh = 0;*/

	//��������� ������� ���������� ������� �������� � ������� ���������� �������� � ������� ���������� �������

	double v1x = ch1->vx, v1y = ch1->vy, v2x = ch2->vx, v2y = ch2->vy;
	double v1xh = 0, v1yh = 0, v2xh = 0, v2yh = 0;
	double rx1 = 0, rx2 = 0, ry1 = 0, ry2 = 0;
	//�����, ������������ ������� ����� ����� ���������� (xp, ch1->y)

	//����� ������ ������� �������� �� ��� ���� ���
	double a = ( ( ch1->m *v1y * (xp - ch1->x) ) + ( ch2->m *v2x * (yp - ch2->y) )+ ( ch2->m *v2y * (xp - ch2->x) ) );
	double b = ( (ch1->m) * v1x ) + ( (ch2->m) * v2x );
	double c = ( (ch1->m) * v1y ) + ( (ch2->m) * v2y );
	double d = ( ( (ch1->m) * (v1x*v1x + v1y*v1y) ) + ( (ch2->m) * (v2x*v2x + v2y*v2y) ) );

	v2xh = ( a / (yp - (ch1->y)) - b) / ( (ch2->m) * ( (yp - (ch2->y)) / (yp - (ch1->y)) - 1 ) );

	v1xh = ( b / ( ch1->m ) - ( v2xh * (ch2->m) / (ch1->m) ) );

	double f = d - (ch1->m * (v1xh*v1xh)) - (ch2->m * v2xh * v2xh);

	double perk = (ch1->m + ((ch1->m) * (ch1->m) / ch2->m));//������ ����������
	double vtornd = (c * (ch1->m) / (ch2->m));//������ ���������� �� ��� �������

	/***************************************************************************/
	//����� ������ �������?
	double vyb_v1y1 = vtornd / perk + (sqrt(vtornd*vtornd + (perk*(f-(c*c/(ch2->m)))) ))/perk;//
	double vyb_v1y2 = vtornd / perk - (sqrt(vtornd*vtornd + (perk*(f-(c*c/(ch2->m)))) ))/perk;
	v1yh = vyb_v1y1;//������ ��� �������

	v2yh = (c - (ch1->m)*v1yh)/(ch2->m);
	//������ �������� �� �������, ��� ����� ���������, ���� ������ � �������, ��� ������������� ���������
	ch1->x = xp; ch2->x = xp; ch2->y = yp; ch1->y = yp;
	ch1->vx = v1xh; ch1->vy = v1yh; ch2->vx = v2xh; ch2->vy = v2yh;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);//��� ������������� GLUT � ������ ��������� ���� ������� glutInit (&argc, argv)

    setlocale(LC_ALL, "Rus");//����������� ������������ ������� ���� � �������
    /***********************************************************************************/
    sbor_info();

    printf("Otladochnay informacia: \n Razmer po y: %d \n Razmer po x: %d, Temperatyra sleva %lg, Temperatyra sprava %lg \n", ys, xs, T_l, T_r);
    printf("����� stepeney svobody (���� ����� ��� ���� �������): %lg \n Kolichestvo molekyl sleva %d \n Kolichestvo molekyl sprava %d \n", i, n_l, n_r);
    printf("Massa molekyly sleva: %lg \n Massa molekyly sprava: %lg \n Otnochenye levoy po x k pravoy po x: %lg \n", m_l, m_r, d);
    /*******************************************************************/
    /*����, �������� ��������� �������
	����� ����������� ������ ������, ������� ��������, ��� �������*/
	getting_ready();
	/*������ � ���� ������� ����� ������ ������ � ���������� � ��� ����� ���������� �� ���� ����� �������� ������
	����� �������, ����� �������� �� ��� ������������� �� ��������*/

    //������ ����� ������� ��������� ������ �� �����
    /************************������� ��� ope_gl****************************/
    //��� ������� ������ ������� (���-�� ��� ���� while ����������� ���������� glutInitDisplayMode (�����),
    // ��� ����� ����� ��������� ��������� �������� GLUT_RGBA � �������� ������������������� ���� (������������ �� ���������)
    //GLUT_RGB � �� ��, ��� � GLUT_RGBA
    //GLUT_INDEX � �������� ��������������� ����
    //GLUT_SINGLE � �������� ��������� �������� ����� (�� ���������)
    //��� ������ ���������� ������� ������������ ����� ������������ ��������� ��� '|'. ��������: glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // ������� ���� �������� glutInitWindowSize (������, ������).
    //glutInitWindowSize(1300, 700);
    glutInitWindowSize(320, 240);
    //������ ������� ���� �� ������, ������� �� ���������� ��� ������� � glutInitWindowPosition (�, �).

    //��������� ���� �������� glutCreateWindow (���������_����).
    glutCreateWindow("�������� �������");

    /*GLUT ��������� ���������-����������� ��������.
    �.�. ���� ������� ����, ������� ����������� ����� �������������, � � ��� ��� �������������� ��� ����������� �������.
    �������� ������� ������� �� ���������� ��� �������� ������� ���� � �.�.
    ���������������� �������-����������� ������� ����� ��� ������ ��������� ������, �� �����, ������ �������� � ����� ����������*/

    //����� glMatrixMode( GL_PROJECTION ); ������ ������� �������� �������
    glMatrixMode(GL_PROJECTION);

    //������������� ������� ������� � �������. ���������� ��� ��������/��������/���������������/�������� � ������� �������.
    glLoadIdentity();

    /*������� gluOrtho2D
    ����: ���������� ���������� ��������������� ��������.

    ���������:
    void gluOrtho2D(GLdouble left ����������� ���� �����, GLdouble right ����������� �����/���, GLdouble bottom ����������� ����� ����, GLdouble top ������������ ������/�����);

    ��������:
    ���������� ������� ���������� ��������������� ��������. ���������� ������� �������� ������������ ������ glOrtho � ����������� near � far, ��������������, ��������������, ������� 0 � 1.

    ���������:
    left, right (��� GLdouble) - ������ ����� � ������ ������� ��������� ���������.

    bottom, top (��� GLdouble) - ������ ������� � ������ ��������� ���������.
    ��� ����������:  ������*/
    //gluOrtho2D(-500, 15000, -2500, 5500);//
    gluOrtho2D(0, 320, 0, 240);
    //glOrtho(0, 480, 480, 0, -1, 1);// ������ �������� ������������ �������

    //������������ ����
    //glutInitWindowPosition(20, 1050 - 480 - 20);

    //void glutDisplayFunc (void (*func) (void)) � ������ ������� ��������� �����������
    glutDisplayFunc(display);

    //void glutIdleFunc (void (*func) (void)) � ������ �������, ���������� ��� ���������� ������ �������, � ����� ���� ����� ��������������
    glutIdleFunc(display);

    //����� ����� ��������� ������� ���� glutMainLoop ().
    glutMainLoop();

    free(arr);
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);//����� ���������
    glClearColor(0.0, 0.4, 0.4, 1.0);//���� ���� -- ���������
    //glClearColor(0.0, 0.0, 0.0, 0.0);//���� ���� -- ������

    glTranslatef(0, 0, 0); //����� ������ ������� ���������.

    /*draw_wall();
    force();*/



    //������ ��������� �������
    /*
    for(int i = 0; i < (n_l + n_r); ++i){

    glBegin(GL_LINES);//��������� � ������ ��������� ����� ������� �� ���� ���? �\�� ������ �����
    glVertex2f(110, 40);
    glVertex2f(220, 200);
    glVertex2f(110, 40);
    glVertex2f(220, 40);
    glVertex2f(110, 200);
    glVertex2f(220, 200);

    glEnd();//����� � ����� ��������� ����� ������� �� ���� ���?
    }
    */

    double sizem = 10;
    //*
    for(int i = 0; i < (n_l + n_r); ++i){
    glBegin(GL_QUADS);//����� �������� ��������
        glColor3f(0.0, 1.0, 0.0);//������������� ���� ����������
        glVertex2i(((arr[i].x)+sizem),((arr[i].y)+sizem));//���������� ������� �������� , � �������� ���������� - 3 ���������� x,y,z, �� ��� ��� ���� 2d, �� ��������� �������������� ���
        glColor3f(0.0, 1.0, 0.0);
        glVertex2i((arr[i].x)+sizem,(arr[i].y));
        glColor3f(0.0, 1.0, 0.0);
        glVertex2i((arr[i].x),(arr[i].y));
        glColor3f(0.0, 1.0, 0.0);
        glVertex2i((arr[i].x) ,(arr[i].y)+sizem);
    glEnd();
    }
    //*/

    //��������� ������
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(0,0);
    glVertex2f(0, ys);
    glVertex2f(0, ys);
    glVertex2f(xs, ys);
    glVertex2f(xs, ys);
    glVertex2f(xs, 0);
    glVertex2f(xs, 0);
    glVertex2f(0,0);
    glEnd();


	//�������� �� ����������� ����� ���������
	//����� ��� �������� \delta t = 10^{-10} / 500 =  2*10^(-13) = 1 / 5000000000000;
    //��������� ���� ������� ������ �������� � ����������� ��������, ������
	//����� ������ � ������ ���� ��� ��������, ���� ����� �� ������, �� ������������� � ����� ����, � ����������� ����� �������� �����
    double t_sp = 0.002;//[c/10^{-10}
    double t_mi = 0.0005;
    double t_ost;
		for(int i = 0; i < (n_l + n_r); ++i){
			t_ost = t_sp;
			//���������� ���������� ����� dt, ������� ����, ��� �� ���� ���� ������� ����� � ��� �����
			double xi = (&arr[i])->x + t_sp*((&(arr[i]))->vx);
			double yi = (&arr[i])->y + t_sp*((&arr[i])->vy);

			//�������� ���������� ������
            if( (xi >= xs) || (xi <=0 )  ||  ( yi >= ys ) || (yi <= 0)  ){
				continue;
			}

			//������ ��������� ������ �� ���� ������
			double ki = 0, bi = 0;
			ki = (yi - ((&arr[i])->y)) / (xi - ((&arr[i])->x));
			bi = (xi * ((&arr[i])->y) - (((&arr[i])->x) * yi)) / (xi - ((&arr[i])->x));

			for(int z = i; z < (n_l + n_r); ++z){


				if(i == z){
					continue;
				}

				//���������� ���������� ����� dt, ������� ����, ��� �� ���� ���� ������� ����� � ��� �����
				double xz = (&arr[z])->x + t_sp*((&arr[z])->vx);
				double yz = (&arr[z])->y + t_sp*((&arr[z])->vy);

				//������ ��������� ������ �� ���� ������
				double kz = 0, bz = 0;

				kz = (yz - ((&arr[z])->y)) / (xz - ((&arr[z])->x));
				bz = (xz * ((&arr[z])->y) - (((&arr[z])->x) * yz)) / (xz - ((&arr[z])->x));

				//���������� ��������� ����� �����������
				double xp = (bi - bz)/(kz - ki);
				double yp = (bi*kz - bz*ki) / (kz - ki);

				int flag_popad = 0;
				//�������� �� ������������ ��������� � "�������"
				flag_popad = peresek(xp, yp, xi, ((&arr[i])->x), xz, ((&arr[z])->x), yi, ((&arr[i])->y), yz, ((&arr[z])->y) );

				//���-�� ������, ����� ���������� ��� ��������� ������������, � ������� ����� ���������� �� ���!!!!!!!
				//�� ���� ������� ��� �� ���!
				if(flag_popad != 0){
					if((xp >= 1) && (yp >= 1) && (xp < xs) && (yp < ys) ){

						//������� �����
						ydar_molekyl(xp, yp,  (&arr[i]), &arr[z], &t_ost);
						t_ost = t_sp - t_ost;
						//move
					}
				}
				//������ ����� ���������

				else{
					//����� ���������, ���� �� ���������� �� ������� �� else if �������, ���� �� ������� �� � ����� z
					// � �  ���� ���� ���������, ��� ����� ����� ����� ��, � � ���� �������� � �������� ��������� � ��� ������� ������� ������ ��� ���
					//
				}

			}
            ////////////

			xi = (&arr[i])->x + t_ost*((&(arr[i]))->vx);
			yi = (&arr[i])->y + t_ost*((&arr[i])->vy);
			//�������� ������ �� ������ � ����� �� ���� ?��� ��? ������� � ����� ������ �������?
			if( (xi <= 0) || (xi>= xs) || (yi <= 0) || (yi >= ys) ){//���� ������� �� ����, ��� ����������� ������
			t_ost = t_mi*1.35;//��� ���� ������ ������� ������ �����
			double tx = 0, ty = 0;
				if(((&arr[i])->vx) >= 0){
					if( ( (&arr[i])->vy) >= 0 ){//�������� ������� � ������ �������
						ty = abs( ((ys-(&arr[i])->y)/((&arr[i])->vy)) );
						tx = abs( ((xs-(&arr[i])->x)/((&arr[i])->vx)) );
						if( ty < tx ){
							((&arr[i])->vy) *= (-1);//���� ������� �������
							(&arr[i])->y = ys;
							(&arr[i])->x += ty * ((&arr[i])->vx);
						}
						else{
							((&arr[i])->vx) *= (-1);//���� ������ �������
							(&arr[i])->y += tx * ((&arr[i])->vy) ;
							(&arr[i])->x = xs;
						}
					}

					else{//�������� ������ � ������ ������
						ty = abs( (((&arr[i])->y)/((&arr[i])->vy)) );
						tx = abs( ((xs-(&arr[i])->x)/((&arr[i])->vx)) );
						if( ty < tx ){
							((&arr[i])->vy) *= (-1);//���� ������ �������
							(&arr[i])->y = 0;
							(&arr[i])->x += tx * ((&arr[i])->vx);
						}
						else{
							((&arr[i])->vx) *= (-1);//���� ������ �������
							(&arr[i])->y += tx * ((&arr[i])->vy);
							(&arr[i])->x = xs;
						}
					}
				}

				else{
					ty = abs( ((ys-(&arr[i])->y)/((&arr[i])->vy)) );
					tx = abs( (((&arr[i])->x)/((&arr[i])->vx)) );
					if(((&arr[i])->vy) >= 0){//�������� ������� � ����� ������
						if( ty < tx ){
							((&arr[i])->vy) *= (-1);//���� ������� �������
							(&arr[i])->y = ys;
							(&arr[i])->x += ty * ((&arr[i])->vx);
						}
						else{
							((&arr[i])->vx) *= (-1);//���� ����� �������
							(&arr[i])->y += tx * ((&arr[i])->vy);
							(&arr[i])->x = xs;
						}
					}

					else{//�������� ������ � ����� ������
						ty = abs( (((&arr[i])->y)/((&arr[i])->vy)) );
						tx = abs( (((&arr[i])->x)/((&arr[i])->vx)) );
						if(  ty < tx ){
							((&arr[i])->vy) *= (-1);//���� ������ �������
							(&arr[i])->y = 0;
							(&arr[i])->x += ty * ((&arr[i])->vx);
						}
						else{
							((&arr[i])->vx) *= (-1);//���� ����� �������
							(&arr[i])->y += tx * ((&arr[i])->vy);
							(&arr[i])->x = 0;
						}
					}
				}
			}

		//������� �������� ������� ����� �� ����� ����� ����������, �� ����� �� ������

			if(t_ost > t_mi){
				move(&arr[i], t_ost);
			}
		}


    glFlush();//���� ���� ��� ����������, ����� � ����� � ����� ��������
}

int randpoz(int minim, int maxim){//���-�� ������� ��-����������, ��� ����� �� ����� ���������
	int a = 0;

    srand(time(NULL));
    Sleep(500);//��� ���� ����� ����� �� ����� ��������� � ����� ����� �����������
    if (minim > 0){
		a = minim+ rand() % (maxim- minim+ 1);
	}

    else{
    	a = minim + rand() % (abs(minim) + maxim+ 1);
	}

    printf("Otladka. Sgenerirovano: %d \n", a);

	return a;
}

void getting_ready(){
	//�������� ������, � ������ ������ �� ������� ar, �� �� ������� ������ ��� ��������, ����, ����� � ������ ����� �������
	arr = (molekyla*)malloc( ( (n_l) + (n_r)) *sizeof(molekyla));

	/**************************************************************************/
	//����, ������ ��������� ��������

	//�����:
	double x_l, x_r;//������ ������
	/*���� ���������� ������ \alpha , �� \frac{(\alpha - 1) - 1}{(xs - 1) - (\alpha + 1)} = d solve for \alpha

	\alpha = ( d*(xs - 2) + 2 ) / (d + 1)*/

	x_l = ( (double)( (d) * (xs - 2) + 2 ) )/ ( (double)(d + 1) ) - 1;
	x_r = ( (double)( (d) * (xs - 2) + 2 ) )/ ( (double)(d + 1) ) + 1;

	x_l = (int)x_l;
	x_r = (int)x_r;

	//������� ��������, ��� ���� ������ ������ , �� ����� ����� ������
	int flag1 = 0;

	//�������� ����� ������� x �  y
	puts("Razmechaem molekyly sleva");
	for(int i = 0; i < (n_l); ++i){


		(&(arr[i]))->x = randpoz(1, x_l);
		(&(arr[i]))->y = randpoz(1, ((ys) - 1) );

		//���������, ��� ���� -- �����

		//�������� �� ���������
		for(int z = 0; (z < i); ++z){
            //������ (&arr[i])->x ����� ������ ����� arr[i].x

			if( ( (&(arr[i]))->x == (&(arr[z]))->x ) && ( (&(arr[i]))->y == (&(arr[z]))->y ) ){
				flag1 ++;
				printf("Bylo vyyavleno nalojenye, ono ystranyetca\n");
			}
		}

		if(flag1 != 0){
			flag1 = 0;
			--i;
			continue;
		}
	}

	//�������� ������ ������� x � y
	puts("Razmechaem molekyle sprava");
	flag1 = 0;
	for(int i = (n_l); i < ((n_r) + (n_l)); ++i){


		(&(arr[i]))->x = randpoz(x_r, ((xs) - 1));
		(&(arr[i]))->y = randpoz(1, ((ys) - 1) );

		//���������, ��� ���� -- �����

		//�������� �� ���������
		for(int z = 0; z < i; ++z){

			if( ( (&(arr[i]))->x == (&(arr[z]))->x ) && ( (&(arr[i]))->y == (&(arr[z]))->y ) ){
				flag1 ++;
				printf("Bylo vyyavleno nalojenye, ono ystranyetca\n");
			}
		}

		if(flag1 != 0){
			flag1 = 0;
			--i;
			continue;
		}
	}
	/**********************************************************/

	//���� ����� ������� �������� �� x � y, ��� ��� ������� i = 3
	//mv^2/2 = i/2kT <=> V^2 = ikT/m <=> V = (ikT/m)^(1/2);
	//��� ����, ��� ����� ���������� ����������
	double vsk_l = sqrt(  (1.38*6.02*3*1000*(T_l)/(m_l))  );
	double vsk_r = sqrt(  (1.38*6.02*3*1000*(T_r)/(m_r))  );
	//std::cout<<vsk_l<<vsk_r<<std::endl;
	//���� �������� ����� ����� ������� � ����� ����� �����������
	puts("Zadayom skorostri molekylam sleva");
	flag1 = 0;
	for(int i = 0; i < ((n_l) ); ++i){

		if(flag1%2 == 0){
			++flag1;
			(&(arr[i]))->vx = randpoz(0, vsk_l);
			(&(arr[i]))->vy = sqrt( vsk_l*vsk_l - ((&(arr[i]))->vx)*((&(arr[i]))->vx) );
		}
		else{
			(&(arr[i]))->vy = randpoz(0, vsk_l);
			(&(arr[i]))->vx = sqrt( vsk_l*vsk_l - ((&(arr[i]))->vy)*((&(arr[i]))->vy) );
		}
		(&(arr[i]))->m = m_l;
	}

	puts("Zadayom skorostri molekylam sprava");
	flag1 = 0;
	for(int i = (n_l); i < ((n_r) + (n_l)); ++i){

		if(flag1%2 == 0){
			++flag1;
			(&(arr[i]))->vx = randpoz(0, vsk_r);
			(&(arr[i]))->vy = sqrt( vsk_r*vsk_r - ((&(arr[i]))->vx)*((&(arr[i]))->vx) );
		}
		else{
			(&(arr[i]))->vy = randpoz(0, vsk_r);
			(&(arr[i]))->vx = sqrt( vsk_r*vsk_r - ((&(arr[i]))->vy)*((&(arr[i]))->vy) );
		}

		(&(arr[i]))->m = m_r;
	}
}

void sbor_info(){
	printf("^\n");
	printf("|\n");
	printf("|\n");
	printf("Y*************\n");
	printf("|*     *     *\n");
	printf("|* T_l * T_r *\n");
	printf("|*     *     *\n");
	printf("|*     *     *\n");
	printf("|*     *     *\n");
	printf("|*************\n");
	printf("0------------X ----->\n");

	printf("Vnimaniye! V znacheniye X i Y vkhodit dlina stenok. \n A ikh razmernost', nekotoryye yedinitsy dliny, pridumat' svyazku otnositel'no dliny molekul. \n");
	printf("T_l i T_r izmeryayutsya v Kel'vinakh.\n");
	printf("Poka dlya uproshcheniya, schitayem chto vezde u gaza i = 3.\n Tak zhe budem schitat', chto sosud popolam podelen.");
	puts(" ");
	printf("Y =  [m * 10^-10]\n");
	scanf("%d", &ys);
	printf("X = [m * 10^-10]\n");
	scanf("%d", &xs);
	printf("T_l = ");
	scanf("%lg", &T_l);
	printf("T_r = ");
	scanf("%lg", &T_r);
	puts(" ");
	printf("Vvedite kolichestvo chastits sleva\n");
	scanf("%d", &n_l);
	printf("Vvedite kolichestvo chastits sprava\n");
	scanf("%d", &n_r);
	printf("Vvedite massu chastitsy sleva kg*10^-26\n");
	scanf("%lg", &m_l);
	printf("Vvedite massu chastitsy sprava kg*10^-26\n");
	scanf("%lg", &m_r);
	printf("Vvedite otnosheniye v kotorom razbivayet peregorodka (otrezok po iks leva / otrezok po iks sprava): ");
	scanf("%lg", &d);
}
