package info.viila.android.linearallocfix.lib;

import android.R.integer;

public class LinearAllocFix {
	
	private static LinearAllocFix fixer;
	
	public static LinearAllocFix getInstance() {
		if(fixer == null)
			fixer = new LinearAllocFix();
		return fixer;
	}
	
	private LinearAllocFix() {
        System.loadLibrary("linear-alloc-fix");
	}
	
	public native long current();
	public native long hack();
	public native long debug(int offset, int attr);
}
