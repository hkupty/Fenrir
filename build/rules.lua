RLTemplate = {}

ANDCPTemplate = {}
ORCPTemplate = {}

RLTemplate.__set = function(t,k,v)
	t = t or {}
	t[k] = v
	return t
	end

RLTemplate.as_rule = function(t) -- .as_destination
	str = t._source .. '[' .. t._predicate:as_predicate() .. ']' .. t._action .. t._dest
	return str
end


ins = function(t,v)
	t = t or {}
	t.plist = t.plist or {}
	table.insert(t.plist, v)
	return t
end

_as_predicate = function(t, key)
	str = ""
	for i,v in ipairs(t.plist) do
		if (type(v) == 'table') then
			str = str .. '(' .. v:as_predicate() .. ')'
		else
			str = str .. v
		end
		ending = (i < #t.plist) and key or ""
		str = str .. ending
	end
	return str
end

RLTemplate.SOURCE = function(t,v)	return t:__set("_source",v) end
RLTemplate.PREDICATE = function(t,v)	return t:__set("_predicate",v) end
RLTemplate.ACTION = function(t,v)	return t:__set("_action",v) end
RLTemplate.DEST = function(t,v)		return t:__set("_dest",v) end

ANDCPTemplate.ADD = ins
ORCPTemplate.ADD = ins

ANDCPTemplate.as_predicate  = function(t) return _as_predicate(t,"&") end
ORCPTemplate.as_predicate  = function(t) return _as_predicate(t,"|") end

function rule() return deepcopy(RLTemplate) end

function p_and() return deepcopy(ANDCPTemplate) end
function p_or() return deepcopy(ORCPTemplate) end

function _op(t,v,op) return t .. op .. v end

function GT(t,v) return _op(t,v,">") end
function GE(t,v) return _op(t,v,">=") end
function LT(t,v) return _op(t,v,"<") end
function LE(t,v) return _op(t,v,"<=") end
function EQ(t,v) return _op(t,v,"=") end
function RX(t,v) return _op(t,v,"~") end

function deepcopy(orig)
    local orig_type = type(orig)
    local copy
    if orig_type == 'table' then
        copy = {}
        for orig_key, orig_value in next, orig, nil do
            copy[deepcopy(orig_key)] = deepcopy(orig_value)
        end
        setmetatable(copy, deepcopy(getmetatable(orig)))
    else
        copy = orig
    end
    return copy
end

