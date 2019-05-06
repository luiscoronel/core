package org.midori_browser.midori

import android.annotation.SuppressLint
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.Menu
import android.support.v7.widget.Toolbar
import android.view.MenuItem
import android.widget.Toast

class ActivityTabs : AppCompatActivity() {

    var count:Int = 0
    var toolBar:Toolbar? = null

    @SuppressLint("RestrictedApi")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_tabs)
        setSupportActionBar(findViewById(R.id.toolbarTwo))

        toolBar = findViewById(R.id.toolbarTwo)

        toolBar?.subtitle
        setSupportActionBar(toolBar)

        //To action go back
        var actionBar = supportActionBar
        actionBar?.setDisplayHomeAsUpEnabled(true)
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.app_menu2, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem?)= when (item?.itemId) {

        R.id.actionTabs2 -> {
            //Code

            true
        }
        else -> {
            super.onOptionsItemSelected(item)
        }


    }
}
