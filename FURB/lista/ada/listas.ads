
package Listas is

type No;
type No_Ptr is access No;

type No is record
	valor: String(1 .. 255);
	proximo : No_Ptr;
end record;

type Lista(<>) is tagged private;
	function make return Lista;
	procedure adiciona(This : in out Lista; valor : String);
	procedure imprime(This : in out Lista);

private
type Lista is tagged record
	inicio : No_Ptr;
end record;

end Listas;

