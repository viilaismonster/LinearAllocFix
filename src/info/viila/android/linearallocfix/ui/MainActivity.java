package info.viila.android.linearallocfix.ui;

import info.viila.android.linearallocfix.lib.LinearAllocFix;
import android.hardware.Camera;
import android.os.Bundle;
import android.R.integer;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivity extends Activity implements OnClickListener{

	Button btnDump, btnHack, btnClear;
	LinearLayout log;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		btnDump = (Button)findViewById(R.id.btnDump);
		btnHack = (Button)findViewById(R.id.btnHack);
		btnClear = (Button)findViewById(R.id.btnClear);
		log = (LinearLayout)findViewById(R.id.log);

		btnDump.setOnClickListener(this);
		btnHack.setOnClickListener(this);
		btnClear.setOnClickListener(this);
		Thread tmp;
	}

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.btnDump:
			int [] attrs = {3};
			for(int i = 6; i<= 6;i++) {
				StringBuilder sBuilder = new StringBuilder();
				for(int j:attrs)
					sBuilder.append(LinearAllocFix.getInstance().debug(i, j)+", ");
				addLog(i+"="+sBuilder.toString());
			}
			break;

		case R.id.btnHack:
			addLog("current="+LinearAllocFix.getInstance().current()
					+"\n"+"hack="+LinearAllocFix.getInstance().hack());
			break;
			
		case R.id.btnClear:
			log.removeAllViews();
			break;
		}
	}

	private void addLog(String string) {
		TextView text = new TextView(this);
		text.setText(string);
		log.addView(text, 0);
	}
}
