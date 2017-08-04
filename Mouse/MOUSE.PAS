unit mouse;
interface
 uses dos;
 {Инициализация драйвера мыши:success:true - драйвер успешно загружен
                                      false - ошибка инициализации;
                              num: - число кнопок мыши }
 procedure initmouse(var success:boolean;num:integer);
 
 procedure showcursor;{ Включение отображения курсора на экране}
 procedure hidecursor;{ Выключение отображения курсора на экране}

 {Опредеоение текущего состояния мыши x,y- Координаты курсораж
                                      left,right - true - нажата: false - отпущена}
 procedure mousecondition(var x,y:integer;var left,right:boolean);

 procedure putcursor(x,y:integer); {Установка курсора в точку с координатами x,y}
 function  leftnum(var x,y:integer):word; {Определяет кол-во нажатий кнопки после                                            последнего вызова данной процедуры: возвращает                                            координаты курсора при последнем нажатии}
 function  rightnum(var x,y:integer):word;
 function  mediumnum(var x,y:integer):word;

 implementation
  var reg:registers; {type registers= record case of
                                       0:(AX,BX,CX,DX,BP,SI,DI,DS,ES,FLAG:WORD);
                                       1:(AL,AH,BL,BH,CL,CH,DL,DH:BYTE);
                                       END; }
 procedure initmouse{(var success:boolean;num:integer)};
  begin
   reg.ax:=0;intr($33,reg);
   if reg.ax=1 then success:=true else success:=false;
   num:=reg.bx {success:=reg.ax=$FFFF}
  end;

 procedure showcursor;
  begin
   reg.ax:=1;intr($33,reg);
  end;

 procedure hidecursor;
  begin
   reg.ax:=2;intr($33,reg);
  end;

 procedure mousecondition{(var x,y:integer;var left,right:boolean)};
  begin
   reg.ax:=3;intr($33,reg);
   x:=reg.cx;y:=reg.dx;
   if (reg.bx and 1)=0 then left:=false else left:=true;
   if (reg.bx and 2)=0 then right:=false else right:=true;
{left:=(reg.bx and 1)<>0;right:=(reg.bx and 2)<>0;middle:=(reg.bx and 4)<>0;}
  end;

 procedure putcursor(x,y:integer);
  begin
    reg.ax:=4;
    reg.cx:=x;
    reg.dx:=y;
    intr($33,reg);
   end;
  end;

 {Вспомогательная (скрытая) прцедура; k - Номер кнопки (0, 1, 2)
                                      x,y - коордмеаты курсора при последнем нажатии}
 function getnum(k:integer;var x,y:integer):word;
   begin
    reg.ax:=5;reg.bx:=k;
    intr($33,reg);
    x:=reg.cx; y:=reg.dx;
    getnum:=reg.bx;
   end;

 function  leftnum{(var x,y:integer):word};
  begin
    leftnum:=getnum(0,x,y);
  end;

 function  rightnum{(var x,y:integer):word};
    begin
    rightnum:=getnum(0,x,y);
   end;
 function  mediumnum{(var x,y:integer):word};
    begin            2
      mediumnum:=getnum(0,x,y);
     end;
end.