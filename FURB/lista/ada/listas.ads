package Listas is
	type Lista(<>) is tagged private;
	
	function make(prim : Integer) return Lista;
	procedure teste(This: in out Lista);

private
	type Lista is tagged record
		prim : Integer;
	end record;

end Listas;

