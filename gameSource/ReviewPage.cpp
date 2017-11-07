#include "ReviewPage.h"


#include "minorGems/game/Font.h"

#include "minorGems/util/SettingsManager.h"

#include "minorGems/game/game.h"

#include "buttonStyle.h"


extern Font *mainFont;
extern Font *mainFontReview;


ReviewPage::ReviewPage()
        : mReviewNameField( mainFont, -242, 250, 10, false,
                            translate( "reviewName"), 
                            "abcdefghijklmnopqrstuvwxyz"
                            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                            "1234567890"
                            " ._-" ),
          mReviewTextArea( 
              mainFont, mainFontReview, 0, 0, 800, 320, false, 
              translate( "reviewText" ), 
              "abcdefghijklmnopqrstuvwxyz"
              "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
              "1234567890"
              " !?$%*&()+-='\":;,.\r", NULL ),
          mBackButton( mainFont, -480, -140, translate( "backButton" ) ) {

    const char *choiceList[2] = { translate( "recommendYes" ),
                                  translate( "recommendNo" ) };
    
    mRecommendChoice = 
        new RadioButtonSet( mainFont, 396, 258,
                            2, choiceList,
                            false, 4 ),
    
    
    setButtonStyle( &mBackButton );

    addComponent( &mBackButton );
    mBackButton.addActionListener( this );

    // add name field after so we can hit return in name field
    // and advance to text area without sending a return key to the text area
    addComponent( &mReviewTextArea );    
    addComponent( &mReviewNameField );

    addComponent( mRecommendChoice );


    mReviewNameField.setMaxLength( 20 );

    mReviewNameField.addActionListener( this );

    mReviewNameField.setLabelTop( true );
    }



ReviewPage::~ReviewPage() {
    delete mRecommendChoice;
    }



void ReviewPage::actionPerformed( GUIComponent *inTarget ) {
    if( inTarget == &mBackButton ) {
        setSignal( "back" );
        }
    else if( inTarget == &mReviewNameField ) {
        switchFields();
        }
    }



void ReviewPage::draw( doublePair inViewCenter, 
                         double inViewSize ) {

    doublePair pos = mRecommendChoice->getPosition();
    
    pos.y += 32;
    pos.x += 12;
    
    setDrawColor( 1, 1, 1, 1 );
    mainFont->drawString( translate( "recommend" ), pos, alignRight );
    }



void ReviewPage::step() {
    }





void ReviewPage::makeActive( char inFresh ) {
    if( inFresh ) {        
        }

    mReviewNameField.focus();
    }



void ReviewPage::makeNotActive() {
    }


void ReviewPage::switchFields() {
    if( mReviewNameField.isFocused() ) {
        mReviewTextArea.focus();
        }
    else if( mReviewTextArea.isFocused() ) {
        mReviewNameField.focus();
        }
    }



void ReviewPage::keyDown( unsigned char inASCII ) {
    if( inASCII == 9 ) {
        // tab
        switchFields();
        return;
        }
    }