// https://leetcode.com/problems/valid-number/

/**
 * @param {string} s
 * @return {boolean}
 */
var isNumber = function(s) {
	s = s.replace('E', 'e').replace('+','').replace('-','');
	if (sanityCheck(s) === false) return false;
	const splt = s.split('e')

	let valid1 = isInteger(splt[0]) || isDecimal(splt[0]);
	let valid2 = (splt.length == 2) ? isInteger(splt[1]) : true;
	return valid1 && valid2;
};

const sanityCheck = (s) => {
	const allowed = '.e0123456789';
	let e = 0, dot = 0;

	for (let i=0; i < s.length; i++) {
		if (allowed.includes(s[i]) === false)
			return false;
		e += s[i] == 'e';
		dot += s[i] == '.';
	}

	return e<2 && dot<2;
}

const isInteger = (s) => {
	if (s.length === 0) return false;
	let allowed = '0123456789';
	for (let i=0; i < s.length; i++) {
		if (allowed.includes(s[0]) === false)
			return false;
	}
	return true;
}

const isDecimal = (s) => {
	if (s.length === 0) return false;
	const splt = s.split('.');
	let valid1 = isInteger(splt[0]);
	let valid2 = (splt.length == 2) ? isInteger(splt[1]) : true;
	return valid1 || valid2;
}

