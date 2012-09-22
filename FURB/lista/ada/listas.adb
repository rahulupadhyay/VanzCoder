With Ada.Text_IO; use Ada.Text_IO;

package body Listas is

	function make(prim : Integer) return Lista is
		o : Lista;
	begin
		o.prim := prim;
		return o;
	end;

	procedure teste(This : in out Lista) is
	begin
		Put_Line(integer'image(This.prim));
	end;

end Listas;
