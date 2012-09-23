package NosLista is
	type NoLista(<>) is tagged private; 
	function make(valor_no : Integer) return NoLista;
	function get_valor(This : NoLista) return Integer;

private
	type NoLista is tagged record
		valor : Integer;
	end record;
	
end NosLista;
