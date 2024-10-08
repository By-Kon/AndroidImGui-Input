package com.sak.imgui_input.FloatingWindow;

import android.content.Context;
import android.graphics.PixelFormat;
import android.os.Build;
import android.os.Handler;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;

import com.sak.imgui_input.NativeUtils;
public class KeyboardView {

    private static final String TAG = "Sak-KeyboardView";
    private static final WindowManager.LayoutParams keyboardViewParams = new WindowManager.LayoutParams();
    private final EditText editText;
    private final WindowManager windowManager;
    private String previousText = "";

    public KeyboardView(Context context) {
        editText = new androidx.appcompat.widget.AppCompatEditText(context) {
            @Override
            public boolean dispatchKeyEvent(KeyEvent event) {
                if (event.getAction() == KeyEvent.ACTION_DOWN) {
                    int keyCode = event.getKeyCode();
                    String keyPressed = KeyEvent.keyCodeToString(keyCode);
                    if (keyPressed.equals("KEYCODE_DEL")) {
                        NativeUtils.DeleteInputText();
                    }
                    if (keyPressed.equals("KEYCODE_ENTER")) {
                        NativeUtils.UpdateInputText("\n");
                    }
                }
                return super.dispatchKeyEvent(event);
            }
        };

        windowManager = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
        setupWindowParams();
        windowManager.addView(editText, keyboardViewParams);
        toggleKeyboard(true);

        editText.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                handleTextChanged(s.toString());
            }

            @Override
            public void afterTextChanged(Editable editable) {
            }
        });
    }

    private void setupWindowParams() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            keyboardViewParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY;
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
                keyboardViewParams.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
            }
        } else {
            keyboardViewParams.type = WindowManager.LayoutParams.TYPE_PHONE;
        }
        keyboardViewParams.format = PixelFormat.RGBA_8888;
        keyboardViewParams.flags = WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL;
        keyboardViewParams.gravity = Gravity.LEFT | Gravity.TOP;
        keyboardViewParams.width = 1;
        keyboardViewParams.height = 1;
    }

    private void handleTextChanged(String currentText) {
        String addedCharacters = findAddedCharacters(currentText);
        if (!addedCharacters.isEmpty()) {
            NativeUtils.UpdateInputText(addedCharacters);
        }
        previousText = currentText;
    }

    private String findAddedCharacters(String currentText) {
        StringBuilder addedCharacters = new StringBuilder();
        int length = Math.min(currentText.length(), previousText.length());

        for (int i = 0; i < length; i++) {
            if (currentText.charAt(i) != previousText.charAt(i)) {
                addedCharacters.append(currentText.charAt(i));
            }
        }

        if (currentText.length() > previousText.length()) {
            addedCharacters.append(currentText.substring(previousText.length()));
        }

        return addedCharacters.toString();
    }

    public void toggleKeyboard(final boolean open) {
        new Handler().postDelayed(() -> {
            InputMethodManager imm = (InputMethodManager) editText.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
            if (open) {
                imm.showSoftInput(editText, InputMethodManager.SHOW_FORCED);
            } else {
                imm.hideSoftInputFromWindow(editText.getWindowToken(), 0);
            }
        }, 300);
    }

    public void removeView() {
        if (editText.getParent() != null) {
            toggleKeyboard(false);
            windowManager.removeView(editText);
            FloatWinService.keyboardView = null;
        }
    }
}
