with Ada.Strings.Unbounded;

package Listas is

type No;
type No_Ptr is access No;

type No is record
	valor: Ada.Strings.Unbounded.Unbounded_String;
	proximo : No_Ptr;
end record;

type Lista(<>) is tagged private;
	function make return Lista;
	procedure adiciona(This : in out Lista; valor : Ada.Strings.Unbounded.Unbounded_String);
	procedure imprime(This : in out Lista);
	procedure limpar(This : in out Lista);

private
type Lista is tagged record
	tamanho : Integer;
	inicio : No_Ptr;
end record;

end Listas;

