#include <QRegularExpression>
#include "LDFHighlighter.h"

LDFHighlighter::LDFHighlighter(QTextDocument* parent)
    : QSyntaxHighlighter(parent) {
  HighlightingRule rule;

  keywordFormat.setForeground(QBrush(QColor(0, 0, 255)));

  QStringList keywordPatterns;

  keywordPatterns << "\\bLIN_description_file\\b"
                  << "\\bLIN_protocol_version\\b"
                  << "\\bLIN_language_version\\b"
                  << "\\bLIN_speed\\b"
                  << "\\bNodes\\b"
                  << "\\bMaster\\b"
                  << "\\bSlaves\\b"
                  << "\\bSignals\\b"
                  << "\\bDiagnostic_signals\\b"
                  << "\\bFrames\\b"
                  << "\\bSporadic_frames\\b"
                  << "\\bEvent_triggered_frames\\b"
                  << "\\bDiagnostic_frames\\b"
                  << "\\bNode_attributes\\b"
                  << "\\bSchedule_tables\\b"
                  << "\\bSignal_encoding_types\\b"
                  << "\\bSignal_representation\\b"
                  << "\\blogical_value\\b"
                  << "\\bphysical_value\\b"
                  << "\\bconfigurable_frames\\b"
                  << "\\bLIN_protocol\\b"
                  << "\\bconfigured_NAD\\b"
                  << "\\binitial_NAD\\b"
                  << "\\bproduct_id\\b"
                  << "\\bP2_min\\b"
                  << "\\bST_min\\b"
                  << "\\bN_As_timeout\\b"
                  << "\\bN_Cr_timeout\\b"
                  << "\\bMasterReq\\b"
                  << "\\bSlaveResp\\b"
                  << "\\bAssignFrameId\\b"
                  << "\\bUnAssignFrameId\\b"
                  << "\\bAssignNAD\\b"
                  << "\\bConditionalChangeNAD\\b"
                  << "\\bDataDump\\b"
                  << "\\bSaveConfiguration\\b"
                  << "\\bAssignFrameIdRange\\b"
                  << "\\bFreeFormat\\b"
                  << "\\bReadByIdentifier\\b"
                  << "\\bresponse_error\\b"
                  << "\\bfault_state_signals\\b"
                  << "\\bdelay\\b"
                  << "\\bms\\b"
                  << "\\bkbps\\b";

  IdentifierStart.setForeground(Qt::red);
  rule.pattern = QRegularExpression("[0-9][0-9]*");
  rule.format = IdentifierStart;
  highlightingRules.append(rule);

  IdentifierStart.setForeground(Qt::black);
  rule.pattern = QRegularExpression("[a-zA-Z_][a-zA-Z0-9_]*");
  rule.format = IdentifierStart;
  highlightingRules.append(rule);

  IdentifierStart.setForeground(Qt::red);
  rule.pattern = QRegularExpression("(0x|0X)[0-9a-fA-F]*");
  rule.format = IdentifierStart;
  highlightingRules.append(rule);

  foreach (const QString& pattern, keywordPatterns) {
    rule.pattern = QRegularExpression(pattern);
    rule.format = keywordFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::darkGreen);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
  }
}

void LDFHighlighter::highlightBlock(const QString& text) {
  foreach (const HighlightingRule& rule, highlightingRules) {
    QRegularExpression expression(rule.pattern);
    QRegularExpressionMatchIterator matchIt = expression.globalMatch(text);
    while (matchIt.hasNext()) {
        QRegularExpressionMatch match = matchIt.next();
        int index = match.capturedStart();
        int length = match.capturedLength();
        setFormat(index, length, rule.format);
    }
  }

  setCurrentBlockState(0);

  int startIndex = 0;
  if (previousBlockState() != 1) {
      QRegularExpressionMatch match = commentStartExpression.match(text);
      startIndex = match.hasMatch() ? match.capturedStart() : -1;
  }

  while (startIndex >= 0) {
      QRegularExpressionMatch endMatch = commentEndExpression.match(text, startIndex);
      int endIndex = endMatch.hasMatch() ? endMatch.capturedStart() : -1;
      int commentLength;
      if (endIndex == -1) {
          setCurrentBlockState(1);
          commentLength = text.length() - startIndex;
      } else {
          commentLength = endIndex - startIndex + endMatch.capturedLength();
      }

      setFormat(startIndex, commentLength, multiLineCommentFormat);

      QRegularExpressionMatch startMatch = commentStartExpression.match(text, startIndex + commentLength);
      startIndex = startMatch.hasMatch() ? startMatch.capturedStart() : -1;
  }
}