With Listas; use Listas; -- clase de lista
with noslista; use noslista;

with Ada.Text_IO; use Ada.Text_IO;

Procedure Principal is
	l : Lista := make(1);
	no : NoLista := make(1);

begin
	l.teste;
	put_line(integer'image(no.get_valor));

end Principal;
